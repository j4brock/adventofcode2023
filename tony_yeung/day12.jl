### A Pluto.jl notebook ###
# v0.19.32

using Markdown
using InteractiveUtils

# ╔═╡ f9f028ae-06c4-4779-a12b-0c8fc87b6f53
struct Row
	springs::String
	record::Vector{Int8}
end

# ╔═╡ b1c0bcad-bef0-4515-bdb2-722ef2024c7d
struct Node
	row::Row
	left::Union{Node, Nothing}
	right::Union{Node, Nothing}
	met::Bool
end

# ╔═╡ c0c3d6f4-3ba8-4b1a-8b04-b2d6f3919f49
struct Tree
	root::Node
end

# ╔═╡ 9dac2ff0-9943-11ee-3753-5b87fdcc1425
rows = open("../resources/day12/input.txt") do f
	rows = Row[]
	for line in eachline(f)
		halves = split(line, " ")
		springs = string(halves[1])
		recordstr = halves[2]

		record = Int8[]
		for capture in split(recordstr, ",")
			push!(record, parse(Int8, capture))
		end
		push!(rows, Row(springs, record))
	end
	return rows
end

# ╔═╡ b92a7b9b-d489-4afb-be96-b8221019c0b8
function is_condition_met(springs::String, record::Vector{Int8})
	curridx = 1
	currcount = 0
	recordlen = length(record)
	for (i, char) in enumerate(springs)
		if char == '#'
			currcount += 1
		end
		if char == '.' || i == length(springs)
			if currcount != 0
				if curridx > recordlen || currcount != record[curridx]
					return false
				end
				currcount = 0
				curridx += 1
			end
		end
	end
	return curridx-1 == recordlen
end

# ╔═╡ 7e022493-5287-436a-8807-9a30e9def46f
function generate_node(row::Row)
	springs = row.springs

	first_wild_idx = findfirst(x -> x == '?', springs)
	
	if first_wild_idx != nothing
		s1 = collect(springs)
		s2 = collect(springs)
		s1[first_wild_idx] = '#'
		s2[first_wild_idx] = '.'
		row1 = Row(String(s1), @views(row.record))
		row2 = Row(String(s2), @views(row.record))
		return Node(row, generate_node(row1), generate_node(row2), false)
	else
		return Node(row, nothing, nothing, is_condition_met(springs, @views(row.record)))
	end
end

# ╔═╡ ecbd0709-7d6c-4ee2-93fe-29b36cbccdb7
function count_ways(tree::Tree)
	rootnode = tree.root
	total = 0
	total += count_ways(rootnode.left) + count_ways(rootnode.right)
end

# ╔═╡ 856ac292-0155-482f-bff8-0f6842335325
function count_ways(node::Node)
	if node.left == nothing && node.right == nothing
		return (node.met ? 1 : 0)
	end

	return count_ways(node.left) + count_ways(node.right)
end

# ╔═╡ 6ea07e78-b150-40ed-8551-214e7ea4fb7e
function find_all_possible(row::Row)

	springs = row.springs
	
	rootnode = generate_node(row)
	tree = Tree(rootnode)

	return count_ways(tree)
end

# ╔═╡ ad926d1f-3ff6-4f48-a452-8d84ecae5f67
s = ".#.###.#.######"

# ╔═╡ 964dc4ac-fdf2-423e-b93a-ac97cb4b86db
s1 = "???.###"

# ╔═╡ 2d40d228-8613-4d59-8c42-661d72fbdf5d
record = Int8.([1,1,3])

# ╔═╡ 13aa5623-5431-4c8a-b58e-4571be6f61f5
is_condition_met(s1, record)

# ╔═╡ d4300393-cbb3-433c-a6de-45b8b24db92f
counts = find_all_possible.(rows)

# ╔═╡ 73d4b601-27b1-4e95-b73d-b1fb27566985
part1 = sum(counts)

# ╔═╡ Cell order:
# ╠═f9f028ae-06c4-4779-a12b-0c8fc87b6f53
# ╠═c0c3d6f4-3ba8-4b1a-8b04-b2d6f3919f49
# ╠═b1c0bcad-bef0-4515-bdb2-722ef2024c7d
# ╠═9dac2ff0-9943-11ee-3753-5b87fdcc1425
# ╠═6ea07e78-b150-40ed-8551-214e7ea4fb7e
# ╠═7e022493-5287-436a-8807-9a30e9def46f
# ╠═b92a7b9b-d489-4afb-be96-b8221019c0b8
# ╠═ecbd0709-7d6c-4ee2-93fe-29b36cbccdb7
# ╠═856ac292-0155-482f-bff8-0f6842335325
# ╠═ad926d1f-3ff6-4f48-a452-8d84ecae5f67
# ╠═964dc4ac-fdf2-423e-b93a-ac97cb4b86db
# ╠═2d40d228-8613-4d59-8c42-661d72fbdf5d
# ╠═13aa5623-5431-4c8a-b58e-4571be6f61f5
# ╠═d4300393-cbb3-433c-a6de-45b8b24db92f
# ╠═73d4b601-27b1-4e95-b73d-b1fb27566985
