RzA = [-3954, 313, 5957];
RzB = [3056, -1479, 6070];
RyA = [5289, 6982, 2689];
RyB = [4613, 7992, -579];

rzA = RzA / (norm(RzA));
rzB = RzB / (norm(RzB));
ryA = RyA / (norm(RyA));
ryB = RyB / (norm(RyB));

rxA = cross(rzA,ryA);
rxB = cross(rzB,ryB);

A = [rxA',ryA',rzA'];
B = [rxB',ryB',rzB'];

Ai = inv(A);
Bi = inv(B);