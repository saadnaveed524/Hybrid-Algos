def hybrid_bfs_dfs(graph, start, switch_depth):
    visited = set()
    bfs_queue = [(start, 0)]
    dfs_stack = []
    result = []

    while bfs_queue or dfs_stack:
        if bfs_queue:
            node, depth = bfs_queue.pop(0)
            if node not in visited:
                visited.add(node)
                result.append(node)
                # Use BFS while depth is less than switch_depth
                if depth < switch_depth:
                    for neighbor in graph[node]:
                        if neighbor not in visited:
                            bfs_queue.append((neighbor, depth + 1))
                # Switch to DFS once depth threshold is reached
                else:
                    dfs_stack.append((node, depth))
        elif dfs_stack:
            node, depth = dfs_stack.pop()
            if node not in visited:
                visited.add(node)
                result.append(node)
                # Continue DFS from this node
                for neighbor in graph[node]:
                    if neighbor not in visited:
                        dfs_stack.append((neighbor, depth + 1))

    return result

# Example Graph
graph = {
    'A': ['B', 'C'],
    'B': ['D', 'E'],
    'C': ['F', 'G'],
    'D': [],
    'E': ['H'],
    'F': [],
    'G': [],
    'H': []
}

# Using the Hybrid Algorithm
result = hybrid_bfs_dfs(graph, 'A', 2)
print('Traversal Result:', result)
