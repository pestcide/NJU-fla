#Q = {0,halt_accept,cpa,cpb,rej,rej1,rej2,rej3,rej4,rej5,rej6,rej7,rej8,rej9,rej10,rej11,rej12,rej13,rej14,rejf,clear1,cnta,cntb,movebback}
#S = {a,b}
#G = {a,b,c,_,I,l,e,g,n,p,u,t}
#q0 = 0
#B = _
#F = {halt_accept}
#N = 3

; the transition functions

; State 0: start state
0 a__ a__ *** cpa
0 b__ b__ *** rej
0 ___ ___ *** rej

; cpa,copy a to tape 2
cpa a__ _a_ rr* cpa
cpa ___ ___ *** rej
cpa b__ b__ *** cpb

; cpb,copy b to tape 3
cpb b__ __b r*r cpb
cpb a__ a__ *** rej
cpb ___ ___ lll clear1

; clear1,clear alpha in tape 1
clear1 aab _ab l** clear1
clear1 bab _ab l** clear1
clear1 _ab _ab r** cnta

; cnta, move one a 
cnta _ab __b *l* cntb
cnta __b __b *** halt_accept

; cntb, write b as c into tape 1
cntb _*b c*b r*l cntb
cntb __b c_b r*l cntb
cntb _*_ _*_ **r movebback
cntb ___ ___ **r movebback

; movebback, move head of tape 3 into the last one
movebback _*b _*b **r movebback
movebback __b __b **r movebback
movebback _*_ _*_ **l cnta
movebback ___ ___ **l cnta

; rej
rej a__ a__ l** rej
rej b__ b__ l** rej
rej ___ ___ r** rej1

;rej1
rej1 a__ ___ r** rej1
rej1 b__ ___ r** rej1
rej1 ___ ___ *** rej2

; rej2,Illegal_Input
rej2 ___ I__ r** rej3
rej3 ___ l__ r** rej4
rej4 ___ l__ r** rej5
rej5 ___ e__ r** rej6
rej6 ___ g__ r** rej7
rej7 ___ a__ r** rej8
rej8 ___ l__ r** rej9
rej9 ___ ___ r** rej10
rej10 ___ I__ r** rej11
rej11 ___ n__ r** rej12
rej12 ___ p__ r** rej13
rej13 ___ u__ r** rej14
rej14 ___ t__ r** rejf