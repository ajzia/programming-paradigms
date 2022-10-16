module LIB
  export factorial, rec_factorial
  export gcd, rec_gcd
  export gcd_extended, rec_gcd_extended
  export diophantine_equation

  function Base.factorial(n::UInt64)::UInt64
    if n == 0 
      return 1
    end

    result::UInt64 = 1
    for i in 2:n
      result *= i
    end

    return result
  end

  function rec_factorial(n::UInt64)::UInt64
    if n == 0 
      return 1
    end

    temp::UInt64 = n - 1
    return n * rec_factorial(temp)
  end

  function Base.gcd(x::UInt64, y::UInt64)::UInt64
    if (x == 0 || y == 0)
      return 0
    end

    if (x == 1 || y == 1)
      return 1
    end

    result::UInt64 = 0;

    for i in 1:min(x, y)
      if (x % i == 0 && y % i == 0)
        result = i
      end
    end

    return result
  end

  function rec_gcd(x::UInt64, y::UInt64)::UInt64
    if (y != 0)
      return rec_gcd(y, x % y);
    end

    return x
  end

  function gcd_extended(a::Int64, b::Int64)
    prevx, x = 1, 0
    prevy, y = 0, 1
    
    while (b != 0)
      q = fld(a, b)
      x, prevx = prevx - q*x, x
      y, prevy = prevy - q*y, y
      a, b = b, a % b
    end

    return a, prevx, prevy
  end

  function rec_gcd_extended(a::Int64, b::Int64)
    if (a == 0)
      return (b, 0, 1)
    end

    (gcd, x1, y1) = rec_gcd_extended(b % a, a)

    x = y1 - fld(b, a) * x1
    y = x1

    return (gcd, x, y)
  end

  function diophantine_equation(a::Int64, b::Int64, c::Int64, gcd::Function)
    (x::Int64, y::Int64) = (1, 1)
    if (a == 0 && b == 0)
      if (c == 0) 
        (x, y) = (1, 1)
        return (x, y)
      else
        (x, y) = typemin(Int64), typemin(Int64)
        println("No possible solutions.\n")
        return (x, y)
      end
    end

    (gcd_temp::Int64, x1::Int64, y1::Int64) = gcd(a, b);

    if (c % gcd_temp != 0) 
      (x, y) = (typemin(Int64), typemin(Int64))
      println("No possible solutions.\n")
      return (x, y)
    end

    x = x1 * fld(c, gcd_temp)
    y = y1 * fld(c, gcd_temp)
    
    return (x, y)
  end
end
