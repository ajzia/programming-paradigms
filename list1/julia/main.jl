# julia main.jl
include("lib.jl")
using .LIB

TEST_ARRAY = [(13, 5, 1), (27, 4, 3), (15, 5, 25), (1, 1, 1), (0, 0, 0), (0, 0, 1), (0, 1, 0), (12, 73, 96)] 

function diophantine_equation_test() 
  println("================ [DIOPHANTINE  EQUASION] ================\n")
  for (a, b, c) in TEST_ARRAY
    println("Diophantine equation for a = $(a), b = $(b), c = $(c)\n")
    for (name, f) in [("Iterative ", gcd_extended), ("Recursive ", rec_gcd_extended)]
      println("$(name) algorithm:");
      (x, y) = diophantine_equation(a, b, c, f)
      if (x != typemin(Int64)) 
        println("Solution found!")
        println("$(a) * $(x) + $(b) * $(y) = $(c)\n");
      end
    end
    println("---------------------------------------------------------\n");
  end
end

function main(args::Array{String})
  x::UInt64 = 5
  y::UInt64 = 27
  z::UInt64 = 57

  println("====================== [FACTORIAL] ======================\n")
  println("Factorial:           $(factorial(x))")
  println("Recursive Facotrial: $(rec_factorial(x))\n")

  println("========================= [GCD] =========================\n")
  println("GCD for           a = $(y), b = $(z): $(gcd(y, z))")
  println("Recursive GCD for a = $(y), b = $(z): $(rec_gcd(y, z))\n")

  diophantine_equation_test()

end

if abspath(PROGRAM_FILE) == @__FILE__
  main(ARGS)
end
