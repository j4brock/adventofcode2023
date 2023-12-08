### A Pluto.jl notebook ###
# v0.19.32

using Markdown
using InteractiveUtils

# ╔═╡ afcedb40-956c-11ee-29b3-673158d3123a
struct Hand
	cards::String
	bid::Int64
end

# ╔═╡ 7454c463-8913-4bc3-9f5d-2ad4fb5fab1e
@enum HandType HIGH ONE_PAIR TWO_PAIR THREE_KIND FULL_HOUSE FOUR_KIND FIVE_KIND

# ╔═╡ 305ce41d-edb9-4d25-bfea-dd61a49132be
cardval = Dict('2' => 2, '3' => 3, '4' => 4, '5' => 5, '6' => 6, '7' => 7, '8' => 8, '9' => 9, 'T' => 10, 'J' => 1, 'Q' => 12, 'K' => 13, 'A' => 14)

# ╔═╡ e495c3e9-cfe9-4f6d-8780-d084ba05747c
hands = open("../resources/day7/input.txt") do f
	hands = Hand[]
	for line in eachline(f)
		regex = match(r"(\w+) (\d+)", line)
		cards = string(regex.captures[1])
		bid = parse(Int64, regex.captures[2])

		push!(hands, Hand(cards, bid))
	end
	return hands
end

# ╔═╡ 890ba57b-4c01-46ed-a73a-1977fea67dce
function countmap(items::T) where {T}
	counts = Dict{eltype(T), Int64}()
	for item in items
		if haskey(counts, item)
			counts[item] += 1
		else
			counts[item] = 1
		end
	end
	return counts
end

# ╔═╡ 018ffce9-f9ff-49b1-8e1e-5a0477dc28b8
begin 
	function has_five_of_kind(counts::Dict{Char, Int64}) 
		return 5 in values(counts)
	end
	function has_four_of_kind(counts::Dict{Char, Int64}) 
		return 4 in values(counts)
	end
	function has_full_house(counts::Dict{Char, Int64}) 
		return 3 in values(counts) && 2 in values(counts)
	end
	function has_three_of_kind(counts::Dict{Char, Int64})
		return 3 in values(counts)
	end
	function has_two_pair(counts::Dict{Char, Int64})
		countcounts = countmap(values(counts))
		return 2 in values(countcounts)
	end
	function has_pair(counts::Dict{Char, Int64})
		return 2 in values(counts)
	end
end;

# ╔═╡ b66e586d-962e-4c18-a74c-e42b0c492348
function get_hand_type(cards::String)
	counts = countmap(cards)
	if has_five_of_kind(counts)
		return FIVE_KIND
	elseif has_four_of_kind(counts)
		return FOUR_KIND
	elseif has_full_house(counts)
		return FULL_HOUSE
	elseif has_three_of_kind(counts)
		return THREE_KIND
	elseif has_two_pair(counts)
		return TWO_PAIR
	elseif has_pair(counts)
		return ONE_PAIR
	else
		return HIGH
	end
end

# ╔═╡ c8c1ec6c-40d1-4a88-93f2-882198491b03
function Base.isless(hand1::Hand, hand2::Hand)
	type1 = get_hand_type(hand1.cards)
	type2 = get_hand_type(hand2.cards)
	if type1 == type2
		for (i, card1) in enumerate(hand1.cards)
			card2 = hand2.cards[i]
			cardval1 = cardval[card1]
			cardval2 = cardval[card2]
			if cardval1 != cardval2
				return cardval1 < cardval2
			end
		end
		error("Exact same hand??")
	end
	return type1 < type2
end

# ╔═╡ e598c711-be72-49ac-864e-824a371ca49f
s1 = "12345"

# ╔═╡ b4aecc7e-478a-4658-9e55-bca646f730b2
sortedhands = copy(hands)

# ╔═╡ 4bce3912-3790-4d4d-9ddb-5fbb4e9c6de8
sort!(sortedhands; rev=true)

# ╔═╡ 95a01017-3f95-43f6-a9b8-3e0a0a11bcd5
weightedbids = (length(sortedhands):-1:1) .* [hand.bid for hand in sortedhands]

# ╔═╡ af7c4bc4-4020-4b69-9ea6-724cfdba6eed
part1 = sum(weightedbids)

# ╔═╡ Cell order:
# ╠═afcedb40-956c-11ee-29b3-673158d3123a
# ╠═7454c463-8913-4bc3-9f5d-2ad4fb5fab1e
# ╠═305ce41d-edb9-4d25-bfea-dd61a49132be
# ╠═e495c3e9-cfe9-4f6d-8780-d084ba05747c
# ╠═b66e586d-962e-4c18-a74c-e42b0c492348
# ╠═018ffce9-f9ff-49b1-8e1e-5a0477dc28b8
# ╠═890ba57b-4c01-46ed-a73a-1977fea67dce
# ╠═c8c1ec6c-40d1-4a88-93f2-882198491b03
# ╠═e598c711-be72-49ac-864e-824a371ca49f
# ╠═b4aecc7e-478a-4658-9e55-bca646f730b2
# ╠═4bce3912-3790-4d4d-9ddb-5fbb4e9c6de8
# ╠═95a01017-3f95-43f6-a9b8-3e0a0a11bcd5
# ╠═af7c4bc4-4020-4b69-9ea6-724cfdba6eed
