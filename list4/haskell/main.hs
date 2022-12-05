factorial :: (Eq p, Num p, Enum p) => p -> p
factorial 0 = 1
factorial n = product [1..n]

gcd' :: (Integral a) => a -> a -> a
gcd' a 0 = a
gcd' a b = gcd' b (a `mod` b)

rec_gcd_extended :: (Integral a) => a -> a -> (a, a, a)
rec_gcd_extended a 0 = (a, 1, 0)
rec_gcd_extended a b = (g, y, x - (a `div` b) * y)
    where (g, x, y) = rec_gcd_extended b (a `mod` b)

diophantine_equation :: (Integral a) => a -> a -> a -> (a, a)
diophantine_equation a b c = (x, y)
    where (_, x, y) = rec_gcd_extended a b
