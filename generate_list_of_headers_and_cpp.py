import os

for root, directories, filenames in os.walk('headers/'):
    for filename in filenames: 
        if filename.endswith('.h') or filename.endswith('.cpp'): 
            print os.path.join(root,filename)

for root, directories, filenames in os.walk('src/'):
    for filename in filenames:
        if filename.endswith('.h') or filename.endswith('.cpp'):
            print os.path.join(root,filename)

for root, directories, filenames in os.walk('Engine/'):
    for filename in filenames:
        if filename.endswith('.h') or filename.endswith('.cpp'):
            print os.path.join(root,filename) 
