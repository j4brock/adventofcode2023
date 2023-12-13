### A Pluto.jl notebook ###
# v0.19.32

using Markdown
using InteractiveUtils

# ╔═╡ 5843ced3-c0fb-4554-8633-bcf936aa5c79
using Printf

# ╔═╡ 42baf8b2-0a55-400c-804a-6fcda2daffed
struct Maze
	startpos::Tuple{Int64, Int64}
	tiles::Matrix{Char}
end

# ╔═╡ 6fbdf6fc-2bc1-4d42-83e3-ec9109e476e9
struct Node
	prevdist::Int64
	pos::CartesianIndex
end

# ╔═╡ 44f15520-9718-11ee-11b6-ed698fa5d2a8
maze = open("../resources/day10/sample1.txt") do f

	lines = String[]
	for line in eachline(f)
		push!(lines, line)
	end

	tiles = Matrix{Char}(undef, length(lines), length(lines[1]))
	startpos = (-1, -1)
	for (i, line) in enumerate(lines)
		chars = collect(line)
		if 'S' in chars
			startpos = (i, findall(x -> x == 'S', chars)[1])
		end
		tiles[i, :] = chars
	end

	return Maze(startpos, tiles)
end

# ╔═╡ 69a093eb-1df3-4215-8410-3fd13a6b5b89
s = ["...13.5", "Hello"]

# ╔═╡ b6d02b59-c3ea-4158-b941-7aefd7e1a0c0
function can_go_up(currchar::Char)
	return currchar in ['|', 'L', 'J', 'S']
end

# ╔═╡ dc8c1f33-943c-428c-b638-4c5560e61b83
function can_go_left(currchar::Char)
	return currchar in ['-', '7', 'J', 'S']
end

# ╔═╡ f673134e-3225-486b-910e-fc7f63dcc6ca
function can_go_right(currchar::Char)
	return currchar in ['-', 'F', 'L', 'S']
end

# ╔═╡ 355b1a23-5055-49f6-8b8a-b5c371cca241
function can_go_down(currchar::Char)
	return currchar in ['|', '7', 'F', 'S']
end

# ╔═╡ 8db21916-0fd4-41a1-81f4-1868e519dadc
function handle_new_node(curr::Node, distmaze::Matrix{Int64}, stack::Vector{Node}, newpos::Tuple{Int64, Int64})
	nextci = CartesianIndex(newpos)
	nevervisted = distmaze[nextci] == -1

	if nevervisted
		newnode = Node(curr.prevdist + 1, nextci)
		push!(stack, newnode)
	end
end

# ╔═╡ 8d94d10e-3066-43c2-8595-3f10a9f372a6
function is_valid_next_char(nextchar::Char, offset::Tuple{Int64, Int64})
	if offset == (-1, 0)
		validchars = ['|', '7', 'F']
	elseif offset == (1, 0)
		validchars = ['|', 'L', 'J']
	elseif offset == (0, -1)
		validchars = ['-', 'F', 'L']
	elseif offset == (0, 1)
		validchars = ['-', 'J', '7']
	else
		error("Oops")
	end
	return nextchar in validchars
end

# ╔═╡ b6ea6f93-877d-45d2-a019-7f39f8044557
function traverse(maze::Maze)
	tiles = maze.tiles
	(nrows, ncols) = size(tiles)
	startpos = CartesianIndex(maze.startpos)
	distmaze = -1 .* ones(Int64, nrows, ncols)

	queue = Node[]
	push!(queue, Node(-1, startpos))

	while ~isempty(queue)
		curr = popfirst!(queue)
		pos = curr.pos
		if distmaze[curr.pos] != -1
			alreadydist = distmaze[curr.pos]
			if curr.prevdist + 1 < alreadydist
				println(alreadydist)
				distmaze[curr.pos] = curr.prevdist + 1
			end
		else
			distmaze[curr.pos] = curr.prevdist + 1
		end
		i = pos[1]; j = pos[2]
		currchar = tiles[curr.pos]
		
		iminus = (i > 1) && can_go_up(currchar)
		iplus = (i < nrows) && can_go_down(currchar)
		jminus = (j > 1) && can_go_left(currchar)
		jplus = (j < ncols) && can_go_right(currchar)
		
		if iminus && is_valid_next_char(tiles[i-1, j], (-1, 0))
			handle_new_node(curr, distmaze, queue, (i-1, j))
		end
		if jminus && is_valid_next_char(tiles[i, j-1], (0, -1))
			handle_new_node(curr, distmaze, queue, (i, j-1))
		end
		if jplus && is_valid_next_char(tiles[i, j+1], (0, 1))
			handle_new_node(curr, distmaze, queue, (i, j+1))
		end
		if iplus && is_valid_next_char(tiles[i+1, j], (1, 0))
			handle_new_node(curr, distmaze, queue, (i+1, j))
		end
	end
	
	return distmaze
end

# ╔═╡ 35bea6ed-dc21-49d4-97fe-2b213d01cbb0
maze

# ╔═╡ 816929a2-8cf3-4f12-9810-29b696922e0b
traversed = traverse(maze)

# ╔═╡ 029ba84d-c452-40b0-9e00-007bb8dcadf7
part1 = maximum(traversed)

# ╔═╡ a41552f5-834d-4759-a1de-48cdd56559a2
function write_to_file(tiles::Matrix{Char}, traversed::Matrix{Int64})
	(nrows, ncols) = size(tiles)
	outfile = open("../resources/day10/out1.txt", "w")
	
	for i = 1:nrows
		for j = 1:ncols
			if traversed[i, j] == -1
				write(outfile, "O")
			else
				write(outfile, tiles[i, j])
			end
		end
		write(outfile, "\n")
	end
	
	close(outfile)
end

# ╔═╡ 09cf37be-5ad3-40b5-88e8-3b4be5fbe82f
write_to_file(maze.tiles, traversed)

# ╔═╡ 00000000-0000-0000-0000-000000000001
PLUTO_PROJECT_TOML_CONTENTS = """
[deps]
Printf = "de0858da-6303-5e67-8744-51eddeeeb8d7"
"""

# ╔═╡ 00000000-0000-0000-0000-000000000002
PLUTO_MANIFEST_TOML_CONTENTS = """
# This file is machine-generated - editing it directly is not advised

julia_version = "1.9.2"
manifest_format = "2.0"
project_hash = "f604830d70fa58877def5710c5d1fa32dcb3f998"

[[deps.Printf]]
deps = ["Unicode"]
uuid = "de0858da-6303-5e67-8744-51eddeeeb8d7"

[[deps.Unicode]]
uuid = "4ec0a83e-493e-50e2-b9ac-8f72acf5a8f5"
"""

# ╔═╡ Cell order:
# ╠═5843ced3-c0fb-4554-8633-bcf936aa5c79
# ╠═42baf8b2-0a55-400c-804a-6fcda2daffed
# ╠═6fbdf6fc-2bc1-4d42-83e3-ec9109e476e9
# ╠═44f15520-9718-11ee-11b6-ed698fa5d2a8
# ╠═69a093eb-1df3-4215-8410-3fd13a6b5b89
# ╠═b6ea6f93-877d-45d2-a019-7f39f8044557
# ╠═b6d02b59-c3ea-4158-b941-7aefd7e1a0c0
# ╠═dc8c1f33-943c-428c-b638-4c5560e61b83
# ╠═f673134e-3225-486b-910e-fc7f63dcc6ca
# ╠═355b1a23-5055-49f6-8b8a-b5c371cca241
# ╠═8db21916-0fd4-41a1-81f4-1868e519dadc
# ╠═8d94d10e-3066-43c2-8595-3f10a9f372a6
# ╠═35bea6ed-dc21-49d4-97fe-2b213d01cbb0
# ╠═816929a2-8cf3-4f12-9810-29b696922e0b
# ╠═029ba84d-c452-40b0-9e00-007bb8dcadf7
# ╠═a41552f5-834d-4759-a1de-48cdd56559a2
# ╠═09cf37be-5ad3-40b5-88e8-3b4be5fbe82f
# ╟─00000000-0000-0000-0000-000000000001
# ╟─00000000-0000-0000-0000-000000000002
