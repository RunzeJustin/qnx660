[
default_image=4m
len=0
attr="?-bigendian"
attr="linker=\"(3,6;2;0x4001)ldrel -s!* -p %(f==0,-l -t 0x%t%)%(f!=0,-x -b 0x%h%) %(d!=0, -d 0x%d%) %i %o\""
vboot=0xfe400000 
+rsvd_vaddr
]
