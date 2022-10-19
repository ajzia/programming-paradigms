using Libdl

function factorial_wrapper(n::UInt64)::UInt64
  func = dlsym(library, "factorial")  # importing function
  result::Int64 = ccall(func, UInt64, (UInt64,), n) # calling the imported function, ccall(function, return type, (argument types), arguments...)

  return result;
end

function rec_factorial_wrapper(n::UInt64)::UInt64
  func = dlsym(library, "rec_factorial") 
  result::Int64 = ccall(func, UInt64, (UInt64,), n) 

  return result;
end

function gcd_wrapper(a::UInt64, b::UInt64)::UInt64
  func = dlsym(library, "gcd") 
  result::Int64 = ccall(func, UInt64, (UInt64, UInt64), a, b) 

  return result;
end

function rec_gcd_wrapper(a::UInt64, b::UInt64)::UInt64
  func = dlsym(library, "rec_gcd") 
  result::Int64 = ccall(func, UInt64, (UInt64, UInt64), a, b) 

  return result;
end

function diophantine_equation_wrapper(a::Int64, b::Int64, c::Int64)::Tuple{Int64, Int64}
  func = dlsym(library, "diophantine_equation") 
  d::Ref{Int64} = 0
  e::Ref{Int64} = 0
  ccall(func, Cvoid, (Int64, Int64, Int64, Ref{Int64}, Ref{Int64}), a, b, c, d, e) 

  return (d[], e[]);
end

function rec_diophantine_equation_wrapper(a::Int64, b::Int64, c::Int64)::Tuple{Int64, Int64}

  func = dlsym(library, "rec_diophantine_equation") 
  d::Ref{Int64} = 0
  e::Ref{Int64} = 0
  ccall(func, Cvoid, (Int64, Int64, Int64, Ref{Int64}, Ref{Int64}), a, b, c, d, e) 

  return (d[], e[])
end

TEST_ARRAY = [(13, 5, 1), (27, 4, 3), (15, 5, 25), (1, 1, 1), (0, 0, 0), (0, 0, 1), (0, 1, 0)] 

function diophantine_equation_test() 
  println("================ [DIOPHANTINE  EQUASION] ================\n")
  for (a, b, c) in TEST_ARRAY
    println("Diophantine equation for a = $(a), b = $(b), c = $(c)\n")
    for (name, f) in [("Iterative ", diophantine_equation_wrapper), ("Recursive ", rec_diophantine_equation_wrapper)]
      println("$(name) algorithm:");
      (x, y) = f(a, b, c)
      if (x != typemin(Int64)) 
        println("Solution found!")
        println("$(a) * $(x) + $(b) * $(y) = $(c)\n");
      end
    end
    println("---------------------------------------------------------\n");
  end
end

function main(args::Array{String})
  run(`gcc -fpic -shared ../../c/src/lib.c -o lib.so`)  # creating a shared library from .c file

  global library = dlopen("./lib.so");  # opening shared library

  x::UInt64 = 5
  y::UInt64 = 27
  z::UInt64 = 57

  println("====================== [FACTORIAL] ======================\n")
  println("Factorial:           $(factorial_wrapper(x))")
  println("Recursive Facotrial: $(rec_factorial_wrapper(x))\n")

  println("========================= [GCD] =========================\n")
  println("GCD for           a = $(y), b = $(z): $(gcd_wrapper(y, z))")
  println("Recursive GCD for a = $(y), b = $(z): $(rec_gcd_wrapper(y, z))\n")

  diophantine_equation_test()
end

if abspath(PROGRAM_FILE) == @__FILE__
  main(ARGS)
end