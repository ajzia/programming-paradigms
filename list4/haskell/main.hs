factorial :: (Eq p, Num p, Enum p) => p -> p
factorial n = product [1..n]

gcd' :: (Integral a) => a -> a -> a
gcd' a 0 = a
gcd' a b = gcd' b (a `mod` b)

gcd_extended :: (Integral a) => a -> a -> (a, a, a)
gcd_extended a 0 = (a, 1, 0)
gcd_extended a b = (g, y, x - (a `div` b) * y)
                   where (g, x, y) = gcd_extended b (a `mod` b)

diophantine_equation :: (Integral a) => a -> a -> a -> (a, a)
diophantine_equation 0 0 0 = (0, 0)
diophantine_equation 0 0 _ = error "No solution."
diophantine_equation a b c | c `mod` g /= 0             = error "No solution."
                           | otherwise                  = (x * (c `div` g), y * (c `div` g))
                             where (g, x, y) = gcd_extended a b
