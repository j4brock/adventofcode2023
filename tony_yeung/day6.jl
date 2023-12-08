### A Pluto.jl notebook ###
# v0.19.32

using Markdown
using InteractiveUtils

# ╔═╡ a3999b91-7ff8-49f4-b880-8ed49a8564af
struct Race
	time::Int64
	distance::Int64
end

# ╔═╡ 6ddae720-9557-11ee-2afd-d3db57511498
races = open("../resources/day6/input.txt") do f
	timeStr = readline(f)
	distStr = readline(f)
	timematch = collect(eachmatch(r"(\d+)", timeStr))
	distmatch = collect(eachmatch(r"(\d+)", distStr))
	races = Race[]
	for (i, match) in enumerate(timematch)
		push!(races, Race(parse(Int64, match.match), parse(Int64,distmatch[i].match)))
	end
	return races
end

# ╔═╡ 482e81ff-b780-4282-9cc1-d09f6bdde908
function find_num_ways(race::Race)
	time = race.time
	t = 1:time
	dist = @. (time - t) * t
	beat = @. dist > race.distance
	return sum(beat)
end

# ╔═╡ d2c32f86-f375-46e7-b1dd-b80d3a28a357
day1 = prod(find_num_ways.(races))

# ╔═╡ 79e0b503-17b3-44f8-8437-0d8ec80449bf
function combine_races(races::Vector{Race})
	timestr = [string(race.time) for race in races]
	diststr = [string(race.distance) for race in races]
	time = parse(Int64, prod(timestr))
	dist = parse(Int64, prod(diststr))
	return Race(time, dist)
end

# ╔═╡ f9df5e7c-18fd-4c62-96c0-0cd9b31838ce
race = combine_races(races)

# ╔═╡ 4a045abf-ede8-44a4-ad50-279027552962
part2 = find_num_ways(race)

# ╔═╡ Cell order:
# ╠═a3999b91-7ff8-49f4-b880-8ed49a8564af
# ╠═6ddae720-9557-11ee-2afd-d3db57511498
# ╠═482e81ff-b780-4282-9cc1-d09f6bdde908
# ╠═d2c32f86-f375-46e7-b1dd-b80d3a28a357
# ╠═79e0b503-17b3-44f8-8437-0d8ec80449bf
# ╠═f9df5e7c-18fd-4c62-96c0-0cd9b31838ce
# ╠═4a045abf-ede8-44a4-ad50-279027552962
