file = "out.xbmc"

s1 = b"\x00\x01\x0F" + (b"\x11" * 23)
s3 = b"\x00\x01\x00" + (b"\xAA" * 23)
s2 = b"\xFF" * 26

stream = s1 + s2 + s3 + s2


with open(file, "wb") as f:
  f.write(stream)
  