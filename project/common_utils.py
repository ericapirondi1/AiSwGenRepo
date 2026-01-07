#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
common_utils.py
===============

Shared utilities for:
- swCmpBuildCheck.py
- swCmpDocsGenerator.py
- unitTestsLauncher.py

Includes:
- logging helpers
- preflight requirements checks
- robust subprocess runner with safe decoding (Windows-friendly)
- docker mount path conversion (cross-platform)
- safe file helpers
"""

from __future__ import annotations

import os
import sys
import shutil
import subprocess
from pathlib import Path
from typing import Optional


# -------------------------
# Logging helpers
# -------------------------
def info(msg: str):  print(f"[INFO] {msg}")
def warn(msg: str):  print(f"[WARN] {msg}")
def error(msg: str): print(f"[ERROR] {msg}")
def fatal(msg: str, code: int = 1):
    print(f"[FATAL] {msg}")
    sys.exit(code)


# -------------------------
# Requirements / preflight
# -------------------------
def require_python(min_major=3, min_minor=8):
    if sys.version_info < (min_major, min_minor):
        fatal(
            f"Python {min_major}.{min_minor}+ required. "
            f"Found {sys.version_info.major}.{sys.version_info.minor}"
        )

def require_command(cmd: str):
    if shutil.which(cmd) is None:
        fatal(f"Required command not found in PATH: '{cmd}'")

def require_file(path: Path, desc: str):
    if not path.is_file():
        fatal(f"{desc} not found: {path}")

def require_dir(path: Path, desc: str):
    if not path.is_dir():
        fatal(f"{desc} not found: {path}")


# -------------------------
# Robust command runner
# -------------------------
def run_cmd(cmd: list[str], cwd: Optional[Path] = None, check: bool = True) -> subprocess.CompletedProcess:
    """
    Run a command capturing output as bytes and decoding safely.
    Prevents UnicodeDecodeError on Windows (cp1252).
    """
    info("Running: " + " ".join(cmd) + (f" (cwd={cwd})" if cwd else ""))

    try:
        p = subprocess.run(
            cmd,
            cwd=str(cwd) if cwd else None,
            capture_output=True  # bytes
        )
    except FileNotFoundError:
        fatal(f"Command not found: {cmd[0]} (is it installed and in PATH?)")
    except PermissionError as e:
        fatal(f"Permission denied running: {' '.join(cmd)}\nDetails: {e}")
    except Exception as e:
        fatal(f"Unexpected error while running: {' '.join(cmd)}\nDetails: {repr(e)}")

    stdout = p.stdout.decode("utf-8", errors="replace") if p.stdout else ""
    stderr = p.stderr.decode("utf-8", errors="replace") if p.stderr else ""

    # Attach decoded text so callers can reuse it
    p.stdout_text = stdout  # type: ignore
    p.stderr_text = stderr  # type: ignore

    if check and p.returncode != 0:
        error(f"Command failed with exit code {p.returncode}: {' '.join(cmd)}")
        if stdout.strip():
            print("---- STDOUT ----")
            print(stdout)
        if stderr.strip():
            print("---- STDERR ----")
            print(stderr)
        raise subprocess.CalledProcessError(p.returncode, cmd, output=stdout, stderr=stderr)

    return p


# -------------------------
# Docker daemon check
# -------------------------
def require_docker_running():
    """Checks that Docker daemon is accessible."""
    try:
        run_cmd(["docker", "info"], check=True)
    except Exception:
        fatal(
            "Docker is installed but not running or not accessible.\n"
            "Start Docker Desktop / Docker daemon and ensure you have permissions."
        )


# -------------------------
# Docker mount path conversion (cross-platform)
# -------------------------
def docker_mount_path(p: Path) -> str:
    """
    Convert a local path to a Docker-friendly mount path.
    - Windows: C:\\repo\\proj -> /c/repo/proj
    - Linux/macOS: /home/user/proj -> /home/user/proj
    """
    abs_p = p.resolve()
    if os.name == "nt":
        drive = abs_p.drive.rstrip(":").lower()
        rel = str(abs_p).split(":", 1)[-1].lstrip("\\/").replace("\\", "/")
        return f"/{drive}/{rel}"
    else:
        return str(abs_p)


# -------------------------
# Safe helpers
# -------------------------
def safe_unlink(p: Path):
    try:
        if p.exists():
            p.unlink()
    except Exception as e:
        warn(f"Could not remove {p}: {e}")

def safe_restore(backup: Optional[Path], dest: Path):
    """Restore backup if present."""
    if backup and backup.exists():
        try:
            shutil.move(str(backup), str(dest))
        except Exception as e:
            warn(f"Could not restore backup {backup} -> {dest}: {e}")
