import os
import shutil
from filecmp import cmp

def copy_file(src, dest):
    os.makedirs(os.path.dirname(dest), exist_ok=True)
    shutil.copy2(src, dest)
    print(f"拷贝文件: {src} -> {dest}")

def should_exclude(path, exclude_dirs):
    abs_path = os.path.abspath(path)
    for exclude_dir in exclude_dirs:
        abs_exclude_dir = os.path.abspath(exclude_dir)
        if os.path.commonpath([abs_path, abs_exclude_dir]) == abs_exclude_dir:
            print(f"排除路径: {path}")
            return True
    return False

def detect_incremental_updates(new_version_dir, old_version_dir, delta_dir, exclude_dirs=None):
    if exclude_dirs is None:
        exclude_dirs = []

    total_files = 0
    copied_files = 0

    for root, _, files in os.walk(new_version_dir):
        if should_exclude(root, exclude_dirs):
            continue
        
        for file in files:
            total_files += 1
            new_file_path = os.path.join(root, file)
            old_file_path = os.path.join(old_version_dir, os.path.relpath(new_file_path, new_version_dir))
            delta_file_path = os.path.join(delta_dir, os.path.relpath(new_file_path, new_version_dir))

            if not os.path.exists(old_file_path):
                print(f"新增文件: {new_file_path}")
                copy_file(new_file_path, delta_file_path)
                copied_files += 1
            elif not cmp(new_file_path, old_file_path, shallow=False):
                print(f"文件已修改: {new_file_path}")
                copy_file(new_file_path, delta_file_path)
                copied_files += 1


    print(f"总文件数: {total_files}")
    print(f"拷贝文件数: {copied_files}")
    print(f"增量文件夹路径: {delta_dir}")

if __name__ == "__main__":
    new_version_dir = "E:/vs/MSST-WebUI"  # 替换为新版本文件夹路径
    old_version_dir = "E:/vs/MSST-WebUI-InnoSetup"  # 替换为旧版本文件夹路径
    delta_dir = "E:/vs/msst"       # 替换为增量文件夹路径
    exclude_dirs = ["pretrain"]  # 替换为要排除的路径

    detect_incremental_updates(new_version_dir, old_version_dir, delta_dir, exclude_dirs)
