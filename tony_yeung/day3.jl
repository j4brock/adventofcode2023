### A Pluto.jl notebook ###
# v0.19.32

using Markdown
using InteractiveUtils

# ╔═╡ 39218cce-e85c-4b2b-8a2c-6a18de70ad4f
struct Schematic
	engine::Matrix{Char}
end

# ╔═╡ 6a06e290-93d4-11ee-324f-9b695149c33e
scheme = open("../resources/day3/input.txt") do f
	raw = String[]
	for l in eachline(f)
		push!(raw, l)
	end
	
	temp = Matrix{Char}(undef, length(raw), length(raw[1]))
	for i in eachindex(raw)
		temp[i, :] = collect(raw[i])
	end
	Schematic(temp)
end

# ╔═╡ 0b2c7b76-2b9e-440b-ac07-e4cf3a6a7e32
function get_numeric_indices(engine::Matrix{Char}, ci::CartesianIndex)
	(nrows, ncols) = size(engine)
	i = ci[1]; j = ci[2]
	iminus = (i-1 > 0); iplus = (i+1 <= nrows)
	jminus = (j-1 > 0); jplus = (j+1 <= ncols)
	indices = CartesianIndex[]
	# top row
	if iminus
		if jminus
			if isnumeric(engine[i-1, j-1])
				push!(indices, CartesianIndex(i-1, j-1))
			end
		end
		
		if isnumeric(engine[i-1, j])
				push!(indices, CartesianIndex(i-1, j))
		end
		
		if jplus
			if isnumeric(engine[i-1, j+1])
				push!(indices, CartesianIndex(i-1, j+1))
			end
		end
	end

	# middle row
	if jminus
		if isnumeric(engine[i, j-1])
			push!(indices, CartesianIndex(i, j-1))
		end
	end

	if jplus
		if isnumeric(engine[i, j+1])
			push!(indices, CartesianIndex(i, j+1))
		end
	end

	# bottom row
	if iplus
		if jminus
			if isnumeric(engine[i+1, j-1])
				push!(indices, CartesianIndex(i+1, j-1))
			end
		end

		if isnumeric(engine[i+1, j])
			push!(indices, CartesianIndex(i+1, j))
		end

		if jplus
			if isnumeric(engine[i+1, j+1])
				push!(indices, CartesianIndex(i+1, j+1))
			end
		end
	end

	indices
end

# ╔═╡ e444f8f7-dc90-43bb-891f-0f92a7be0247
function get_number_str(engine::Matrix{Char}, ci::CartesianIndex)
	i = ci[1]; j = ci[2]
	(nrows, ncols) = size(engine)
	curr = engine[i, j]
	currj = j-1;
	while currj > 0 && isnumeric(engine[i, currj])
		curr = engine[i, currj] * curr
		currj -= 1
	end

	currj = j+1
	while currj <= ncols && isnumeric(engine[i, currj])
		curr = curr * engine[i, currj]
		currj += 1
	end

	curr
end

# ╔═╡ 0897b250-20bd-458f-a803-c92bf56cc6c8
function issymbol(char::Char)
	asciival = convert(Int64, char)
	return !((asciival >= 48 && asciival <= 57) || asciival == 46)
end

# ╔═╡ 5d42acee-3ed5-4650-9f9e-f922d8964f38
function get_part_nums(scheme::Schematic)
	engine = scheme.engine
	engineCI = CartesianIndices(engine)
	partnums = Int64[]
	for ci in eachindex(engineCI)
		if issymbol(engine[ci])
			cis = get_numeric_indices(engine, ci)
			numstrs = unique(get_number_str.(Ref(engine), cis))
			nums = parse.(Ref(Int64), numstrs)
			append!(partnums, nums)
		end
	end
	partnums
end

# ╔═╡ 2117db6e-1140-403e-9e0e-06e06ef9f604
partnums = get_part_nums(scheme)

# ╔═╡ e67eafb7-c668-4489-879a-1aee51bdd630
part1 = sum(partnums)

# ╔═╡ b26c2019-c267-4cb7-85da-c7a799a970e3
function isstar(char::Char)
	asciival = convert(Int64, char)
	return asciival == 42
end

# ╔═╡ f36aebc6-8930-4c99-b3f6-4ced3f062d3b
function get_gear_ratios(scheme::Schematic)
	engine = scheme.engine
	engineCI = CartesianIndices(engine)
	partnums = Int64[]
	for ci in eachindex(engineCI)
		if isstar(engine[ci])
			cis = get_numeric_indices(engine, ci)
			numstrs = unique(get_number_str.(Ref(engine), cis))
			nums = parse.(Ref(Int64), numstrs)
			if length(nums) == 2
				push!(partnums, nums[1] * nums[2])
			end
		end
	end
	partnums
end

# ╔═╡ c77534c1-64f3-4687-98f0-c8bfa64154a3
b = get_gear_ratios(scheme)

# ╔═╡ 5d9272d1-2dc0-430c-b990-f5f3abaf5a87
part2 = sum(b)

# ╔═╡ Cell order:
# ╠═39218cce-e85c-4b2b-8a2c-6a18de70ad4f
# ╠═6a06e290-93d4-11ee-324f-9b695149c33e
# ╠═5d42acee-3ed5-4650-9f9e-f922d8964f38
# ╟─0b2c7b76-2b9e-440b-ac07-e4cf3a6a7e32
# ╠═e444f8f7-dc90-43bb-891f-0f92a7be0247
# ╠═0897b250-20bd-458f-a803-c92bf56cc6c8
# ╠═2117db6e-1140-403e-9e0e-06e06ef9f604
# ╠═e67eafb7-c668-4489-879a-1aee51bdd630
# ╠═b26c2019-c267-4cb7-85da-c7a799a970e3
# ╠═f36aebc6-8930-4c99-b3f6-4ced3f062d3b
# ╠═c77534c1-64f3-4687-98f0-c8bfa64154a3
# ╠═5d9272d1-2dc0-430c-b990-f5f3abaf5a87
