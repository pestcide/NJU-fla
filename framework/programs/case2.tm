#Q = {0,halt_accept,mv,cmp,acc,acc1,acc2,acc3,rej,rej1,rej2,rej3,rej4,rej5}
#S = {a,b,c}
#G = {a,b,c,_,t,r,u,e,f,l,s}
#q0 = 0
#B = _
#F = {halt_accept}
#N = 2

; the transition functions

; State 0: start state
0 a_ _a rr 0
0 b_ _b rr 0
0 c_ __ rl mv
0 __ __ ** rej

; mv:move head of tape1 to first place
mv ** ** *l mv
mv _* _* *l mv
mv *_ *_ *r cmp
mv __ __ *r cmp

; cmp:compare tape0 and tape1
cmp aa __ rr cmp
cmp bb __ rr cmp
cmp __ __ ** acc
cmp ab ** ** rej
cmp ac ** ** rej
cmp a_ ** ** rej
cmp ba ** ** rej
cmp bc ** ** rej
cmp b_ ** ** rej
cmp ca ** ** rej
cmp cb ** ** rej
cmp c_ ** ** rej
cmp _* ** ** rej

; acc
acc __ t_ r* acc1
acc1 __ r_ r* acc2
acc2 __ u_ r* acc3
acc3 __ e_ r* halt_accept

;rej
rej ** __ rr rej
rej *_ __ r* rej
rej _* __ *r rej
rej __ f_ r* rej1
rej1 __ a_ r* rej2
rej2 __ l_ r* rej3
rej3 __ s_ r* rej4
rej4 __ e_ r* rej5