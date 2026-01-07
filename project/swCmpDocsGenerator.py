#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from __future__ import annotations

import os
import re
import shutil
import subprocess
from pathlib import Path
import sys
from typing import Optional, List, Tuple

from common_utils import (
    info, warn, error, fatal,
    require_python, require_command, require_dir, require_file,
    require_docker_running,
    run_cmd, docker_mount_path,
    safe_unlink, safe_restore
)

IMAGE_NAME = "doxygen-plantuml"

TEMPLATE_DOCKERFILE_PRIMARY = "DoxDockerfile"
TEMPLATE_DOXYFILE_PRIMARY = "Doxygen"
TEMPLATE_DOCKERFILE_FALLBACK = "Dockerfile"
TEMPLATE_DOXYFILE_FALLBACK = "Doxyfile"

DEST_DOCKERFILE = "Dockerfile"
DEST_DOXYFILE = "Doxyfile"


def resolve_template(script_dir: Path, primary: str, fallback: str) -> Path:
    p = script_dir / primary
    if p.is_file():
        return p
    p2 = script_dir / fallback
    if p2.is_file():
        return p2
    fatal(f"Template not found. Tried: {primary} and {fallback} in {script_dir}")
    return p  # unreachable


def preflight_checks(script_dir: Path, codebase_root: Path, template_dockerfile: Path, template_doxyfile: Path):
    info("Performing preflight checks...")
    require_python(3, 8)
    require_command("docker")
    require_dir(script_dir, "Script directory")
    require_dir(codebase_root, "Code directory ('./code')")
    require_file(template_dockerfile, "Template Dockerfile")
    require_file(template_doxyfile, "Template Doxyfile")
    require_docker_running()
    info("Preflight checks OK.")


def find_targets_with_pltf_or_cfg(root: Path):
    for dirpath, dirnames, _ in os.walk(root):
        dirpath = Path(dirpath)
        has_pltf = "pltf" in dirnames and (dirpath / "pltf").is_dir()
        has_cfg = "cfg" in dirnames and (dirpath / "cfg").is_dir()
        if has_pltf or has_cfg:
            yield dirpath


def patch_doxyfile(doxy_path: Path, project_name: str, has_pltf: bool, has_cfg: bool) -> None:
    content = doxy_path.read_text(encoding="utf-8", errors="replace")

    if re.search(r"^\s*PROJECT_NAME\s*=", content, flags=re.MULTILINE):
        content = re.sub(
            r"^\s*PROJECT_NAME\s*=.*$",
            f'PROJECT_NAME           = "{project_name}"',
            content,
            flags=re.MULTILINE,
        )
    else:
        content = f'PROJECT_NAME           = "{project_name}"\n' + content

    inputs = []
    if has_cfg:
        inputs.append("./cfg")
    if has_pltf:
        inputs.append("./pltf")

    input_line = "INPUT                  = " + " ".join(inputs)

    content = re.sub(r"^\s*INPUT\s*=.*$\n?", "", content, flags=re.MULTILINE)
    content = input_line + "\n" + content

    doxy_path.write_text(content, encoding="utf-8")


def main():
    script_dir = Path(__file__).resolve().parent
    codebase_root = script_dir / "code"

    template_dockerfile = resolve_template(script_dir, TEMPLATE_DOCKERFILE_PRIMARY, TEMPLATE_DOCKERFILE_FALLBACK)
    template_doxyfile = resolve_template(script_dir, TEMPLATE_DOXYFILE_PRIMARY, TEMPLATE_DOXYFILE_FALLBACK)

    preflight_checks(script_dir, codebase_root, template_dockerfile, template_doxyfile)

    info(f"Template Dockerfile : {template_dockerfile}")
    info(f"Template Doxyfile   : {template_doxyfile}")
    info(f"Scanning targets in : {codebase_root}")

    targets = list(find_targets_with_pltf_or_cfg(codebase_root))
    if not targets:
        warn("No folders found containing 'pltf' or 'cfg'. Nothing to do.")
        return

    ok_targets: List[Path] = []
    fail_targets: List[Tuple[Path, str]] = []

    for target_dir in targets:
        has_pltf = (target_dir / "pltf").is_dir()
        has_cfg = (target_dir / "cfg").is_dir()
        project_name = target_dir.name

        dest_dockerfile = target_dir / DEST_DOCKERFILE
        dest_doxyfile = target_dir / DEST_DOXYFILE

        docker_backup = None
        doxy_backup = None

        print("------------------------------------------------------------")
        info(f"Target: {target_dir}")
        info(f"  - has cfg : {has_cfg}")
        info(f"  - has pltf: {has_pltf}")
        info(f"  - PROJECT_NAME -> {project_name}")

        try:
            if dest_dockerfile.exists():
                docker_backup = target_dir / (DEST_DOCKERFILE + ".bak")
                shutil.move(str(dest_dockerfile), str(docker_backup))

            if dest_doxyfile.exists():
                doxy_backup = target_dir / (DEST_DOXYFILE + ".bak")
                shutil.move(str(dest_doxyfile), str(doxy_backup))

            shutil.copy2(str(template_dockerfile), str(dest_dockerfile))
            shutil.copy2(str(template_doxyfile), str(dest_doxyfile))

            patch_doxyfile(dest_doxyfile, project_name, has_pltf=has_pltf, has_cfg=has_cfg)

            info(f"[Docker] Building image in: {target_dir}")
            run_cmd(["docker", "build", "-t", IMAGE_NAME, "."], cwd=target_dir, check=True)

            mount = docker_mount_path(target_dir)
            info(f"[Docker] Running doxygen with mount: {mount} -> /workspace")
            run_cmd(["docker", "run", "--rm", "-v", f"{mount}:/workspace", IMAGE_NAME], cwd=target_dir, check=True)

            info("[OK] Documentation generated.")
            ok_targets.append(target_dir)

        except subprocess.CalledProcessError as e:
            msg = f"Command failed (exit={e.returncode})"
            error(f"[FAIL] {target_dir}: {msg}")
            fail_targets.append((target_dir, msg))

        except Exception as e:
            msg = f"Unexpected error: {repr(e)}"
            error(f"[FAIL] {target_dir}: {msg}")
            fail_targets.append((target_dir, msg))

        finally:
            safe_unlink(dest_dockerfile)
            safe_unlink(dest_doxyfile)
            safe_restore(docker_backup, dest_dockerfile)
            safe_restore(doxy_backup, dest_doxyfile)
            info("[Cleanup] Done.\n")

    print("\n============================")
    print("          SUMMARY           ")
    print("============================")
    print(f"SUCCESS ({len(ok_targets)}):")
    for t in ok_targets:
        print(f" - {t}")

    print(f"\nFAILED  ({len(fail_targets)}):")
    for t, msg in fail_targets:
        print(f" - {t} :: {msg}")

    print("============================\n")

    sys.exit(1 if fail_targets else 0)


if __name__ == "__main__":
    main()
