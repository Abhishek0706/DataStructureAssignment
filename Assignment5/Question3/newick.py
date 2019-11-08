from ete3 import Tree
l=[
    ("A","B",7),
    ("E","C",5),
    ("A","D",5),
    ("D","E",1),
    ("D","F",6),
]
t = Tree.from_parent_child_table(l)
s=t.write()
tree=Tree(s)
tree.show()
