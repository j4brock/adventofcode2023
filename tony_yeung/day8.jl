### A Pluto.jl notebook ###
# v0.19.32

using Markdown
using InteractiveUtils

# ╔═╡ 39c65636-851d-4bb8-bf77-bedc30c2f99e
using Printf

# ╔═╡ 4615a8d1-7d52-4675-9852-741275cbe82d
struct Node
	key::String
	left::String
	right::String
end

# ╔═╡ 4adefa5f-0c50-4389-b827-2533ec391659
struct Network
	directions::String
	nodes::Dict{String, Node}
end

# ╔═╡ 17bd93c0-9880-11ee-308d-63bac9f8ba78
network = open("../resources/day8/input.txt") do f

	directions = readline(f)
	readline(f)

	nodemap = Dict{String, Node}()
	for line in eachline(f)
		str = split(line, "=")
		key = strip(string(str[1]))
		valuestr = strip(string(str[2]))
		rmatch = match(r"(\w{3}), (\w{3})", valuestr)

		left = rmatch.captures[1]
		right = rmatch.captures[2]

		newnode = Node(key, left, right)
		nodemap[key] = newnode
	end

	return Network(directions, nodemap)
end

# ╔═╡ fecfb6cd-ab66-492a-a2f0-7bedc9c9cea6
function solve_network_part1(network::Network, endkey = "ZZZ")
	steps = network.directions
	nodemap = network.nodes

	numsteps = 0
	currkey = "AAA"
	currstepidx = 1

	while currkey != endkey
		currstep = steps[currstepidx]
		currnode = nodemap[currkey]
		if currstep == 'L'
			currkey = currnode.left
		elseif currstep == 'R'
			currkey = currnode.right
		else
			error("Oops")
		end
		numsteps += 1
	
		if currstepidx == length(steps)
			currstepidx = 1
		else
			currstepidx += 1
		end
	end
	numsteps
end

# ╔═╡ 7e2b85b0-3025-4c9d-9aaa-7a24b655a24c
part1 = solve_network_part1(network)

# ╔═╡ 1d7c2f98-65ec-4da0-8569-cb385eccac15
function solve_network_part2(network::Network, endkey = "Z")
	steps = network.directions
	nodemap = network.nodes

	numsteps = 0

	currkeys = filter(x -> endswith(x, "A"), keys(nodemap))
	counter = zeros(length(currkeys))
	
	currstepidx = 1
	found = false

	while !found
		currstep = steps[currstepidx]
		currnodes = [nodemap[key] for key in currkeys]
		# [@printf("%s|",x) for x in currkeys]
		if currstep == 'L'
			currkeys = [node.left for node in currnodes]
		elseif currstep == 'R'
			currkeys = [node.right for node in currnodes]
		else
			error("Oops")
		end
		# [@printf("|%s",x) for x in currkeys]
		# println()
		numsteps += 1
		counter .+= 1
	
		if currstepidx == length(steps)
			currstepidx = 1
		else
			currstepidx += 1
		end
		condmet = [endswith(nextkey, endkey) for nextkey in currkeys]

		# for (i, met) in enumerate(condmet)
		#	if met
		#		@printf("%d: %d\n", i, counter[i])
		#		counter[i] = 0
		#	end
		# end
		found = all(condmet)
		# if sum(condmet) > 0
			# println(sum(condmet))
		# end
	end
	numsteps
end

# ╔═╡ f7fefd0d-b4b5-4614-a81a-c292be1d7308
currkeys = filter(x -> endswith(x, "A"), string.(keys(network.nodes)))

# ╔═╡ 5385bc71-b202-4e47-9051-4fd08879f77c
@time solve_network_part2(network)

# ╔═╡ 26cd8f45-a050-432b-88e1-66ff72a4d62e
part2 = lcm([12169, 20659, 20093, 16697, 17263, 13301])

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
# ╠═39c65636-851d-4bb8-bf77-bedc30c2f99e
# ╠═4adefa5f-0c50-4389-b827-2533ec391659
# ╠═4615a8d1-7d52-4675-9852-741275cbe82d
# ╠═17bd93c0-9880-11ee-308d-63bac9f8ba78
# ╠═fecfb6cd-ab66-492a-a2f0-7bedc9c9cea6
# ╠═7e2b85b0-3025-4c9d-9aaa-7a24b655a24c
# ╠═1d7c2f98-65ec-4da0-8569-cb385eccac15
# ╠═f7fefd0d-b4b5-4614-a81a-c292be1d7308
# ╠═5385bc71-b202-4e47-9051-4fd08879f77c
# ╠═26cd8f45-a050-432b-88e1-66ff72a4d62e
# ╟─00000000-0000-0000-0000-000000000001
# ╟─00000000-0000-0000-0000-000000000002
