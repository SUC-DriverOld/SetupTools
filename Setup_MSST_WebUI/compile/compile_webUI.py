import os
import base64

def replace_in_file(input_file: str, output_file: str, target_string: str, replacement_string: str) -> None:
    with open(input_file, 'r', encoding='utf-8') as file:
        content = file.read()
    modified_content = content.replace(target_string, replacement_string)
    with open(output_file, 'w', encoding='utf-8') as file:
        file.write(modified_content)

def encode_webUI(input_file: str) -> str:
    with open(input_file, 'rb') as f:
        return base64.b64encode(f.read()).decode('utf-8')

webui_file = 'webUI.py'
input_filename = 'webui_template.cpp'
output_filename = 'temp.cpp'
string_to_replace = 'STRING_TO_REPLACE'
replacement = encode_webUI('webUI.py')

replace_in_file(input_filename, output_filename, string_to_replace, replacement)
os.system("g++ -std=c++11 -static temp.cpp icon.o -o webui_tmp.exe")
os.unlink(output_filename)
os.system("VMProtect_Con.exe webui_tmp.exe webui.exe -pf webui.exe.vmp")
os.unlink('webui_tmp.exe')
os.system("pause")