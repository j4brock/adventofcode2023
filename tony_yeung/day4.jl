### A Pluto.jl notebook ###
# v0.19.32

using Markdown
using InteractiveUtils

# ╔═╡ 6e8dec6f-14c9-42cd-a693-23467fdb439d
struct Card
	id::Int64
	winning::Vector{Int64}
	numbers::Vector{Int64}
end

# ╔═╡ c4242850-94a6-11ee-0571-27fcb5485de1
cards = open("../resources/day4/input.txt") do f
	cards = Card[]
	for line in eachline(f)
		s1 = split(line, ":")
		cardidstr = string(s1[1]); allnums = string(s1[2])
		cardid = parse(Int64, match(r"\d+", cardidstr).match)

		s2 = split(allnums, "|")
		winnumstr = string(s2[1]); numstr = string(s2[2])
		winnums = parse.(Ref(Int64), getproperty.(collect(eachmatch(r"\d+", winnumstr)), Ref(:match)))
		nums = parse.(Ref(Int64), getproperty.(collect(eachmatch(r"\d+", numstr)), Ref(:match)))

		push!(cards, Card(cardid, winnums, nums))
	end
	cards
end

# ╔═╡ 9badb471-0080-4f48-925e-91bc475ebb04
function get_num_match(card::Card)
	matching = in.(card.numbers, Ref(card.winning))
	nummatch = sum(matching)
end

# ╔═╡ c2e78f66-53e2-47a6-9fde-3e9d11d78ae9
function calculate_num_points(card::Card)
	nummatch = get_num_match(card)
	nummatch > 0 ? 2^(nummatch - 1) : 0
end

# ╔═╡ 21dc84a3-0160-4f2d-8c38-9f68191b5bcf
part1 = sum(calculate_num_points.(cards))

# ╔═╡ 96cf0fa6-56bb-4bcc-96ab-ddd796d46176
function calculate_num_scratchcard(cards::Vector{Card})
	nummatches = get_num_match.(cards)
	toprocess = copy(cards)
	won = Dict{Int64, Int64}()
	while !isempty(toprocess)
		card = popfirst!(toprocess)
		i = card.id
		nummatch = nummatches[i]
		if nummatch > 0
			append!(toprocess, cards[i+1:i+nummatch])
		end

		if i in keys(won)
			won[i] += 1
		else
			won[i] = 1
		end
	end
	won
end

# ╔═╡ 29a4f11b-9c34-4566-b1a9-d99a347b34ac
won = calculate_num_scratchcard(cards)

# ╔═╡ 71472ffa-730e-4e99-b9ca-42e525f37bd6
part2 = sum(values(won))

# ╔═╡ Cell order:
# ╠═6e8dec6f-14c9-42cd-a693-23467fdb439d
# ╠═c4242850-94a6-11ee-0571-27fcb5485de1
# ╠═c2e78f66-53e2-47a6-9fde-3e9d11d78ae9
# ╠═9badb471-0080-4f48-925e-91bc475ebb04
# ╠═21dc84a3-0160-4f2d-8c38-9f68191b5bcf
# ╠═96cf0fa6-56bb-4bcc-96ab-ddd796d46176
# ╠═29a4f11b-9c34-4566-b1a9-d99a347b34ac
# ╠═71472ffa-730e-4e99-b9ca-42e525f37bd6
