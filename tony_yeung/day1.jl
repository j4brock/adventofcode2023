### A Pluto.jl notebook ###
# v0.19.32

using Markdown
using InteractiveUtils

# ╔═╡ 96611ab4-76b4-433b-a1a9-3d37f68f403a
struct Line
	text::String
end

# ╔═╡ c9149526-eb48-4696-a396-80aa792df6f2
numdict = Dict{String, String}("one" => "1", "two" => "2", "three" => "3", "four" => "4", "five" => "5", "six" => "6", "seven" => "7", "eight" => "8", "nine" => "9")

# ╔═╡ 693b40d7-653e-4217-9b03-7bab525856ee
function get_digit_string(s::String)
	temp = tryparse(Int64, s)
	if temp != nothing
		return s
	end
	return get_digit_string(numdict[s])
end

# ╔═╡ 8f843b18-f4fb-4811-b975-5d43dfc68b2b
function get_calibration_value(line::Line)
	p1 = r"([0-9]|zero|one|two|three|four|five|six|seven|eight|nine)"
	p1_rev = r"([0-9]|orez|eno|owt|eerht|ruof|evif|xis|neves|thgie|enin)"
	rev = reverse(line.text)
	digits = [string(regex.match) for regex in eachmatch(p1, line.text)]
	revdigits = [string(regex.match) for regex in eachmatch(p1_rev, reverse(line.text))]

	value = parse(Int64, get_digit_string(digits[1]) * get_digit_string(reverse(revdigits[1])))
end

# ╔═╡ b4bb77e0-90b1-11ee-2ec3-e105d86a047c
lines = open("../resources/day1/input.txt") do f
	lines = Line[]
	for l in eachline(f)
		push!(lines, Line(l))
	end
	lines
end

# ╔═╡ 5d34162c-a58d-4e6b-9d33-aca9850bc54a
calvals = get_calibration_value.(lines)

# ╔═╡ 2afdfb17-0056-470e-8a31-06687b34c600
sum(calvals)

# ╔═╡ Cell order:
# ╠═96611ab4-76b4-433b-a1a9-3d37f68f403a
# ╠═c9149526-eb48-4696-a396-80aa792df6f2
# ╠═8f843b18-f4fb-4811-b975-5d43dfc68b2b
# ╠═693b40d7-653e-4217-9b03-7bab525856ee
# ╠═b4bb77e0-90b1-11ee-2ec3-e105d86a047c
# ╠═5d34162c-a58d-4e6b-9d33-aca9850bc54a
# ╠═2afdfb17-0056-470e-8a31-06687b34c600
