--Collection ids start at 0 and increase by 1

--Collections::add_collection(name, parent_collection_id)
Collections.clear_collections()
Collections.add_collection("Lights", -1)                --0
Collections.add_collection("Indoor Lights", 0)          --1
Collections.add_collection("World", -1)                 --2
Collections.add_collection("World Collision Boxes", 2)  --3

