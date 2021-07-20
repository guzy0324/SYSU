with open('hello_world_raw.com', 'rb') as f:
    codes = f.read(128)
with open('hello_world.com', 'wb') as f:
    f.write(codes)
