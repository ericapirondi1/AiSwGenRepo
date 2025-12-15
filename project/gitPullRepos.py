import os
import re
import shutil
import subprocess
import sys

# Exit codes
EXIT_BAD_GITHUB_URL = 1
EXIT_MISSING_GITHUB_COMMIT_INFO = 2
EXIT_TAG_GITHUB_BAD_FORMED = 3
EXIT_GIT_CLONE_FAILED = 4

def exec_prj_clone_from_github(info, clone_dir):
    def check_github_url(url):
        if not (url.startswith("http") and "//github.com/" in url):
            sys.exit(EXIT_BAD_GITHUB_URL)

    def check_tag(tag):
        if tag is None:
            sys.exit(EXIT_MISSING_GITHUB_COMMIT_INFO)
        if re.fullmatch(r"[0-9A-Za-z._\\-]+", tag) is None:
            sys.exit(EXIT_TAG_GITHUB_BAD_FORMED)

    def force_rmtree(path):
        import stat
        path = os.path.abspath(path)
        def onerror(func, p, exc_info):
            exc = exc_info[1]
            if isinstance(exc, FileNotFoundError):
                return
            try:
                if not os.path.exists(p):
                    return
                os.chmod(p, stat.S_IWRITE)
                func(p)
            except FileNotFoundError:
                return
        if os.path.exists(path):
            shutil.rmtree(path, onerror=onerror)

    check_github_url(info["repository"])
    check_tag(info["tag"])

    # Remove old project if exists
    if os.path.exists(clone_dir):
        force_rmtree(clone_dir)

    CMD = [
        "git",
        "clone",
        "--recurse-submodules",
        "--branch",
        info["tag"],
        info["repository"],
        clone_dir
    ]
    try:
        subprocess.run(CMD, check=True)
    except subprocess.CalledProcessError:
        sys.exit(EXIT_GIT_CLONE_FAILED)


if __name__ == "__main__":
    # Example usage
    repo_info = {
        "repository": "https://github.com/moa2ofo/AiSwGenRepo",
        # Replace with a valid branch or tag from the repo
        "tag": "main"
    }
    target_dir = "./AiSwGenRepo"

    exec_prj_clone_from_github(repo_info, target_dir)
    print(f"Repository cloned into {target_dir}")
