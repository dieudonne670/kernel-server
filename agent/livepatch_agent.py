import ctypes
import requests
import os
import time

SERVER_URL = "http://127.0.0.1:8000"
CHECK_INTERVAL = 5  # seconds

# Keep track of patches we already applied
applied_patches = set()

def load_patch(patch_path):
    print(f"[AGENT] Loading patch: {patch_path}")
    patch = ctypes.CDLL(patch_path)
    try:
        patch.apply_patch()  # Your patch should have an apply_patch() function
        print("[AGENT] Patch applied successfully")
    except Exception as e:
        print(f"[AGENT] Failed to apply patch: {e}")

def get_server_patches():
    try:
        response = requests.get(f"{SERVER_URL}/patches")
        return response.json()
    except Exception as e:
        print(f"[AGENT] Could not fetch patches: {e}")
        return []

def download_patch(patch_name):
    url = f"{SERVER_URL}/download/{patch_name}"
    local_path = f"/tmp/{patch_name}"
    print(f"[AGENT] Downloading patch {patch_name} from {url}")
    try:
        r = requests.get(url)
        with open(local_path, "wb") as f:
            f.write(r.content)
        return local_path
    except Exception as e:
        print(f"[AGENT] Failed to download patch: {e}")
        return None

def run_agent():
    print("[AGENT] Livepatch agent started")
    while True:
        patches = get_server_patches()
        for patch_name in patches:
            if patch_name not in applied_patches:
                path = download_patch(patch_name)
                if path:
                    load_patch(path)
                    applied_patches.add(patch_name)
        time.sleep(CHECK_INTERVAL)

if __name__ == "__main__":
    run_agent()
