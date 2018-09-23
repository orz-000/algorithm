import sys

import heapq

class Node:
    def __init__(self, x):
        self.data  = x
        self.left  = None
        self.right = None

    def insert(self,node, x):
        if node is None: return Node(x)
        elif x == node.data: return node
        elif x < node.data:
            node.left = self.insert(node.left, x)
        else:
            node.right = self.insert(node.right, x)
        return node

    def traverse(self,node):
        if node:
            self.traverse(node.left)
            print(node.data)
            self.traverse(node.right)


inp = "AIZUWAKAMATASUINAWASIROKITAKATAKORIYAMA"
heap = []
data = {}
mini1 = mini2 = ()
for i in range(len(inp)):
    data[inp[i]] = data.get(inp[i],0) + 1

data = {v:k for k,v in data.items()}
print(data)
list = tuple(data.items())
new_node = ()

for i in range(len(list)):
    heapq.heappush(heap,list[i])

mini1 = heapq.heappop(heap)
mini2 = heapq.heappop(heap)

sum = int(mini1[0]) + int(mini2[0])
new_node = (sum,)
nod = Node(mini1)
nod.insert(nod,mini2)
heapq.heappush(heap,new_node)

while(True):
        if(len(heap) <= 1):break
        mini1 = heapq.heappop(heap)
        mini2 = heapq.heappop(heap)
        sum = int(mini1[0]) + int(mini2[0])
        new_node = (sum,)
        nod.insert(nod,mini1)
        nod.insert(nod,mini2)
        heapq.heappush(heap,new_node)

#nod.traverse(nod)
