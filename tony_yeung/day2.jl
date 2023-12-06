### A Pluto.jl notebook ###
# v0.19.32

using Markdown
using InteractiveUtils

# ╔═╡ 148671f9-a5d1-47e0-8575-67ebe9623a7b
struct Game
	id::Int64
	red::Vector{Int64}
	green::Vector{Int64}
	blue::Vector{Int64}
end

# ╔═╡ fdee3df0-9159-11ee-17e9-51c4b5777e03
games = open("../resources/day2/input.txt") do f
	games = Game[]
	for l in eachline(f)
		first = split(l, ":")
		gameidstr = match(r"[0-9]+", first[1]).match
		rounds = split(first[2], ";")

		reds = Int64[]
		greens = Int64[]
		blues = Int64[]
		for i in eachindex(rounds)
			red = 0
			green = 0
			blue = 0
			for regex in eachmatch(r"([0-9]+) (red|green|blue)", rounds[i])
				capture = regex.captures
				num = parse(Int64, capture[1])
				color = capture[2]
				if color == "red" && red == 0
					red = num
				elseif color == "green" && green == 0
					green = num
				elseif color == "blue" && blue == 0
					blue = num
				else
					error("Oops")
				end
			end
			push!(reds, red)
			push!(greens, green)
			push!(blues, blue)
		end
		push!(games, Game(parse(Int64, gameidstr), reds, greens, blues))
	end
	games
end

# ╔═╡ 12b1b4f3-14d9-4502-9ac2-66acd88e39fa
function is_valid_game(game::Game; red = 12, green = 13, blue = 14)
	for i in eachindex(game.red)
		if game.red[i] > red || game.green[i] > green || game.blue[i] > blue
			return false
		end
	end
	return true
end

# ╔═╡ b3788596-7c7e-4063-adf4-e7b7bf36b2d8
list = filter(is_valid_game, games)

# ╔═╡ 2d31d40d-1a58-4df4-9508-db7e9146570f
function find_answer(list::Vector{Game})
	sum(getproperty.(list, Ref(:id)))
end

# ╔═╡ 9103030a-a684-47af-8e4d-1bd9abf5ec4c
find_answer(list)

# ╔═╡ 8a6c20fc-bc14-43f8-b646-0ddd5ed208b3
function find_minimum_num_colors(game::Game)
	(maximum(game.red), maximum(game.green), maximum(game.blue))
end

# ╔═╡ d588dc4c-1770-420f-a752-f746b456be1b
mincolors = find_minimum_num_colors.(games)

# ╔═╡ 57a6d49f-8884-4017-911b-a6f5d13e320e
powers = prod.(mincolors)

# ╔═╡ 5fef669c-991e-4958-9493-d6fff9ad4a01
sum(powers)

# ╔═╡ Cell order:
# ╠═148671f9-a5d1-47e0-8575-67ebe9623a7b
# ╠═fdee3df0-9159-11ee-17e9-51c4b5777e03
# ╠═b3788596-7c7e-4063-adf4-e7b7bf36b2d8
# ╠═12b1b4f3-14d9-4502-9ac2-66acd88e39fa
# ╠═2d31d40d-1a58-4df4-9508-db7e9146570f
# ╠═9103030a-a684-47af-8e4d-1bd9abf5ec4c
# ╠═8a6c20fc-bc14-43f8-b646-0ddd5ed208b3
# ╠═d588dc4c-1770-420f-a752-f746b456be1b
# ╠═57a6d49f-8884-4017-911b-a6f5d13e320e
# ╠═5fef669c-991e-4958-9493-d6fff9ad4a01
