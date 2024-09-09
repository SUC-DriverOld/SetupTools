import base64

with open('webUI.py', 'rb') as f:
    encoded = base64.b64encode(f.read())

with open('webUI.bin', 'wb') as f:
    f.write(encoded)
