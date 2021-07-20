with open('hello_world_msg1.com', 'rb') as f:
    codes = f.read()
data1 = codes[-128:]
with open('good.com', 'wb') as f:
    f.write(codes + data1)
with open('hello_world_msg2.com', 'rb') as f:
    codes = f.read()
with open('evil.com', 'wb') as f:
    f.write(codes + data1)
