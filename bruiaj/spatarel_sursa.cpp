#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std;

typedef struct LineI{
    long long A;
    long long B;
    long long C;
}LineI;
typedef struct LineD{
    double A;
    double B;
    double C;
}LineD;

typedef struct PointI{
    long long X;
    long long Y;
}PointI;
typedef struct PointD{
    double X;
    double Y;
}PointD;
struct PointP {
    double dist;
    double alfa;
};

typedef struct SegI{
    PointI A;
    PointI B;
    LineI  L;
}SegI;
typedef struct SegD{
    PointD A;
    PointD B;
    LineD  L;
}SegD;

double PI = 3.14159265358979323846264338327950288419716939937510;

double Eps = 0.000001;

LineD LineItoLineD(LineI L) {
	LineD ans;
	ans.A = (double)L.A;
	ans.B = (double)L.B;
	ans.C = (double)L.C;
	return ans;
}

long long AbsI(long long val){
    if (val > 0)
        return  val;
    else
        return -val;
}
double AbsD(double val){
    if (val > 0)
        return  val;
    else
        return -val;
}

//calculeaza distanta dintre doua puncte
double DistI(PointI &A, PointI &B){
    return sqrt((double)(A.X - B.X) * (A.X - B.X) + (A.Y - B.Y) * (A.Y - B.Y));
}
double DistD(PointD &A, PointD &B){
    return sqrt((A.X - B.X) * (A.X - B.X) + (A.Y - B.Y) * (A.Y - B.Y));
}

//calculeaza distanta dintre un punct si o dreapta
double DistI(PointI &P, LineI &L){
	return abs(L.A * P.X + L.B * P.Y + L.C) / (sqrt(L.A * L.A + L.B * L.B));
}
double DistD(PointD &P, LineD &L){
	return fabs(L.A * P.X + L.B * P.Y + L.C) / (sqrt(L.A * L.A + L.B * L.B));
}

//calculeaza coef. a,b,c ai unei drepte, pe baza a doua pct. de pe aceasta
LineI DreaptaI(PointI &A, PointI &B){
    LineI sol;
    sol.A=A.Y - B.Y;
    sol.B=B.X - A.X;
    sol.C=A.X * B.Y - B.X * A.Y;
    return sol;
}
LineD DreaptaD(PointD &A, PointD &B){
    LineD sol;
    sol.A=A.Y - B.Y;
    sol.B=B.X - A.X;
    sol.C=A.X * B.Y - B.X * A.Y;
    return sol;
}

//calculeaza intersectia a doua drepte ((-inf,-inf) pt. nici un pct. comun si (inf,inf) pt. o inf de pct. comune)
PointD InterLineI(LineI &A, LineI &B){
    PointD sol;
    if (A.A*B.B == B.A*A.B){
        if (A.A*B.C == B.A*A.C &&
            A.B*B.C == B.B*A.C){
            sol.X = sol.Y = 2000000000;
        }else{
            sol.X = sol.Y =-2000000000;
        }
    }else{
        sol.X = (double)(B.C*A.B - A.C*B.B) / (A.A*B.B - B.A*A.B);
        sol.Y = (double)(B.C*A.A - A.C*B.A) / (A.B*B.A - A.A*B.B);
    }
    return sol;
}
PointD InterLineD(LineD &A, LineD &B){
    PointD sol;
    if (AbsD(A.A*B.B - B.A*A.B) <= Eps){
        if (AbsD(A.A*B.C - B.A*A.C) <= Eps &&
            AbsD(A.B*B.C - B.B*A.C) <= Eps){
            sol.X = sol.Y = 2000000000;
        }else{
            sol.X = sol.Y =-2000000000;
        }
    }else{
        sol.X = (B.C*A.B - A.C*B.B) / (A.A*B.B - B.A*A.B);
        sol.Y = (B.C*A.A - A.C*B.A) / (A.B*B.A - A.A*B.B);
    }
    return sol;
}

long long SgnI(PointI &P, LineI &L){
    return L.A * P.X + L.B * P.Y + L.C;
}
double SgnD(PointD &P, LineD &L){
    return L.A * P.X + L.B * P.Y + L.C;
}

//initializeaza un segment
SegI SetSegI(PointI &A, PointI &B){
    SegI sol;
    sol.A = A;
    sol.B = B;
    sol.L = DreaptaI(A,B);
    return sol;
}
SegD SetSegD(PointD &A, PointD &B){
    SegD sol;
    sol.A = A;
    sol.B = B;
    sol.L = DreaptaD(A,B);
    return sol;
}

//calculeaza intersectia a doua segmente ((-inf,-inf) pt. nici un pct. comun si (inf,inf) pt. o inf de pct. comune)
PointD InterSegI(SegI &A, SegI &B){
    PointD sol, aa, ab, ba, bb;
    aa.X = (double)A.A.X;
    aa.Y = (double)A.A.Y;
    ab.X = (double)A.B.X;
    ab.Y = (double)A.B.Y;
    ba.X = (double)B.A.X;
    ba.Y = (double)B.A.Y;
    bb.X = (double)B.B.X;
    bb.Y = (double)B.B.Y;
    sol = InterLineI(A.L, B.L);
    if (sol.X != -2000000000 && sol.X != 2000000000){
        if (AbsD(DistD(aa,sol) + DistD(sol,ab) - DistD(aa,ab)) > Eps || AbsD(DistD(ba,sol) + DistD(sol,bb) - DistD(ba,bb)) > Eps)
            sol.X = sol.Y =-2000000000;
    }
    if (sol.X == 2000000000){
        double DA = DistD(aa, ab);
        double DB = DistD(ba, bb);
        double DAA = DistD(aa, ba);
        double DAB = DistD(aa, bb);
        double DBA = DistD(ab, ba);
        double DBB = DistD(ab, bb);
        if ((AbsD(DA + DAA + DB - DBB) <= Eps && DAA > Eps) ||
            (AbsD(DA + DAB + DB - DBA) <= Eps && DAB > Eps) ||
            (AbsD(DA + DBA + DB - DAB) <= Eps && DBA > Eps) ||
            (AbsD(DA + DBB + DB - DAA) <= Eps && DBB > Eps))
            sol.X = sol.Y =-2000000000;
        if ((AbsD(DA + DB - DBB) <= Eps && DAA <= Eps) ||
            (AbsD(DA + DB - DBA) <= Eps && DAB <= Eps))
            sol = aa;
        if ((AbsD(DA + DB - DAB) <= Eps && DBA <= Eps) ||
            (AbsD(DA + DB - DAA) <= Eps && DBB <= Eps))
            sol = ab;
    }
    return sol;
}
PointD InterSegD(SegD &A, SegD &B){
    PointD sol;
    sol = InterLineD(A.L, B.L);
    if (sol.X != -2000000000 && sol.X != 2000000000){
        if (AbsD(DistD(A.A,sol) + DistD(sol,A.B) - DistD(A.A,A.B)) > Eps || AbsD(DistD(B.A,sol) + DistD(sol,B.B) - DistD(B.A,B.B)) > Eps)
            sol.X = sol.Y =-2000000000;
    }
    if (sol.X == 2000000000){
        double DA = DistD(A.A, A.B);
        double DB = DistD(B.A, B.B);
        double DAA = DistD(A.A, B.A);
        double DAB = DistD(A.A, B.B);
        double DBA = DistD(A.B, B.A);
        double DBB = DistD(A.B, B.B);
        if ((AbsD(DA + DAA + DB - DBB) <= Eps && DAA > Eps) ||
            (AbsD(DA + DAB + DB - DBA) <= Eps && DAB > Eps) ||
            (AbsD(DA + DBA + DB - DAB) <= Eps && DBA > Eps) ||
            (AbsD(DA + DBB + DB - DAA) <= Eps && DBB > Eps))
            sol.X = sol.Y =-2000000000;
        if ((AbsD(DA + DB - DBB) <= Eps && DAA <= Eps) ||
            (AbsD(DA + DB - DBA) <= Eps && DAB <= Eps))
            sol = A.A;
        if ((AbsD(DA + DB - DAB) <= Eps && DBA <= Eps) ||
            (AbsD(DA + DB - DAA) <= Eps && DBB <= Eps))
            sol = A.B;
    }
    return sol;
}

//calculeaza intersectia a doua segmente ((-inf,-inf) pt. nici un pct. comun si (inf,inf) pt. o inf de pct. comune)
PointD InterSegNonTgI(SegI &A, SegI &B){
    PointD sol;
    sol = InterSegI(A,B);
    if ((sol.X == A.A.X && sol.Y == A.A.Y) || (sol.X == A.B.X && sol.Y == A.B.Y) || (sol.X == B.A.X && sol.Y == B.A.Y) || (sol.X == B.B.X && sol.Y == B.B.Y)){
        sol.X = sol.Y =-2000000000;
    }
    return sol;
}
PointD InterSegNonTgD(SegD &A, SegD &B){
    PointD sol;
    sol = InterSegD(A,B);
    if ((sol.X == A.A.X && sol.Y == A.A.Y) || (sol.X == A.B.X && sol.Y == A.B.Y) || (sol.X == B.A.X && sol.Y == B.A.Y) || (sol.X == B.B.X && sol.Y == B.B.Y)){
        sol.X = sol.Y =-2000000000;
    }
    return sol;
}

//compara pozitia a doua puncte
int ComparePointsI(const void *p1, const void *p2){
    PointI P1,P2;
    P1=*(PointI*)p1;
    P2=*(PointI*)p2;
    if ((P1.X > P2.X) || (P1.X == P2.X && P1.Y > P2.Y))
        return  1;
    else
        return -1;
}
int ComparePointsD(const void *p1, const void *p2){
    PointD P1,P2;
    P1=*(PointD*)p1;
    P2=*(PointD*)p2;
    if ((P1.X - P2.X > Eps) || (AbsD(P1.X - P2.X) <= Eps && P1.Y - P2.Y > Eps))
        return  1;
    else
        return -1;
}

void Sortare(void *Data, int Data0, size_t size_t, int (*CompFct)(const void *p1, const void *p2)){
    char *data=(char*)Data;
    int a,b;
    if (Data0<=4){
        void *tmp=malloc(size_t);
        for(a=0;a<Data0;a++){
            for(b=a+1;b<Data0;b++){
                if (((*CompFct)(data+size_t*a,data+size_t*b))>0){
                    memcpy(tmp,data+size_t*a,size_t);
                    memcpy(data+size_t*a,data+size_t*b,size_t);
                    memcpy(data+size_t*b,tmp,size_t);
                }
            }
        }
    }else{
        int tmp=Data0/2;
        Sortare(Data,tmp,size_t,CompFct);
        Sortare(data+size_t*tmp,Data0-tmp,size_t,CompFct);
        //interschimbare
        char *pos1,*pos2;
        char *POS,*St;
        pos1=data;
        pos2=data+tmp*size_t;
        St=POS=(char*)malloc(Data0*size_t);
        for(;(pos1<data+tmp*size_t)&(pos2<data+Data0*size_t);){
            if (CompFct(pos1,pos2)<0){
                memcpy(POS,pos1,size_t);
                pos1+=size_t;
            }else{
                memcpy(POS,pos2,size_t);
                pos2+=size_t;
            }
            POS+=size_t;
        }
        if (pos1==data+size_t*tmp){
            memcpy(POS,pos2,data+size_t*Data0-pos2);
        }else{
            memcpy(POS,pos1,data+size_t*tmp-pos1);
        }
        memcpy(data,St,size_t*Data0);
        free(St);
    }
}

//calculeaza semnul punctului C fata de dreapta determinata de punctele A si B (0 => A, B si C sunt coliniare)
long long ColI(PointI &A, PointI &B, PointI &C){
    return A.X*B.Y+B.X*C.Y+C.X*A.Y-A.X*C.Y-B.X*A.Y-C.X*B.Y;
}
double ColD(PointD &A, PointD &B, PointD &C){
    return A.X*B.Y+B.X*C.Y+C.X*A.Y-A.X*C.Y-B.X*A.Y-C.X*B.Y;
}

//calculeaza infasuratoarea convexa a mai multor puncte (daca un punct apare de mai multe ori, este eliminat; daca exista mai mult de doua puncte coliniare, care fac parte din infasuratoare, acestea sunt eliminate)
void InfasI(int Lst0, PointI *Lst, int &Sol0, PointI *Sol){
    if (Lst0){
        PointI *Pct, *Coad;
        Pct = (PointI*)malloc(Lst0 * sizeof(PointI));
        memcpy(Pct, Lst, Lst0 * sizeof(PointI));
        Sortare(Pct, Lst0, sizeof(PointI), ComparePointsI);
        int pos = 0;
        int a;
        for(a=1;a<Lst0;a++){
            if (Pct[a].X != Pct[a-1].X || Pct[a].Y != Pct[a-1].Y){
                Pct[++pos] = Pct[a];
            }
        }
        Lst0 = pos+1;
        Coad = Sol-1;
        Pct--;
        int Stop,Stopp;
        Coad[1] = Pct[1];
        Coad[2] = Pct[2];
        Stop = 2;
        for(pos = 3;pos<=Lst0;pos++){
            Coad[++Stop] = Pct[pos];
            for(;Stop>=3 && ColI(Coad[Stop-2], Coad[Stop-1], Coad[Stop])>=0;){
                Coad[Stop-1] = Coad[Stop]; --Stop;
            }
        }
        Stopp = Stop;
        for(pos = Lst0-1;pos>=1;pos--){
            Coad[++Stop] = Pct[pos];
            for(;Stop>=Stopp+2 && ColI(Coad[Stop-2], Coad[Stop-1], Coad[Stop])>=0;){
                Coad[Stop-1] = Coad[Stop]; --Stop;
            }
        }
        Sol0 = Stop-1;
        free(Pct+1);
    }else{
        Sol0 = 0;
    }
}
void InfasD(int Lst0, PointD *Lst, int &Sol0, PointD *Sol){
    if (Lst0){
        PointD *Pct, *Coad;
        Pct = (PointD*)malloc(Lst0 * sizeof(PointD));
        memcpy(Pct, Lst, Lst0 * sizeof(PointD));
        Sortare(Pct, Lst0, sizeof(PointI), ComparePointsD);
        int pos = 0;
        int a;
        for(a=1;a<Lst0;a++){
            if (AbsD(Pct[a].X - Pct[a-1].X) > Eps || AbsD(Pct[a].Y != Pct[a-1].Y) > Eps){
                Pct[++pos] = Pct[a];
            }
        }
        Lst0 = pos+1;
        Coad = Sol-1;
        Pct--;
        int Stop,Stopp;
        Coad[1] = Pct[1];
        Coad[2] = Pct[2];
        Stop = 2;
        for(pos = 3;pos<=Lst0;pos++){
            Coad[++Stop] = Pct[pos];
            for(;Stop>=3 && ColD(Coad[Stop-2], Coad[Stop-1], Coad[Stop])>=0;){
                Coad[Stop-1] = Coad[Stop]; --Stop;
            }
        }
        Stopp = Stop;
        for(pos = Lst0-1;pos>=1;pos--){
            Coad[++Stop] = Pct[pos];
            for(;Stop>=Stopp+2 && ColD(Coad[Stop-2], Coad[Stop-1], Coad[Stop])>=0;){
                Coad[Stop-1] = Coad[Stop]; --Stop;
            }
        }
        Sol0 = Stop-1;
        free(Pct+1);
    }else{
        Sol0 = 0;
    }
}

//determina daca un punct se afla strict in interiorul unui poligon (punctele de pe laturile poligonului nu se afla in interiorul acestuia)
int PointInPolygonNonTgI(int Poly0, PointI *Poly, PointD &P){
    double sgn;
    int a;
    PointI P1,P2;
    PointD P3;
    Poly--;
    P1 = Poly[Poly0];
    P2 = Poly[1];
    P3 = P;
    sgn = P1.X*P2.Y+P2.X*P3.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y;
    if (AbsD(sgn) <= Eps) return 0;
    if (sgn>0){
        for(a=2;a<=Poly0;a++){
            P1 = Poly[a-1];
            P2 = Poly[a];
            if (P1.X*P2.Y+P2.X*P3.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y <= 0) return 0;
        }
    }else{
        for(a=2;a<=Poly0;a++){
            P1 = Poly[a-1];
            P2 = Poly[a];
            if (P1.X*P2.Y+P2.X*P3.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y >= 0) return 0;
        }
    }
    return 1;
}
int PointInPolygonNonTgD(int Poly0, PointD *Poly, PointD &P){
    double sgn;
    int a;
    PointD P1,P2,P3;
    Poly--;
    P1 = Poly[Poly0];
    P2 = Poly[1];
    P3 = P;
    sgn = P1.X*P2.Y+P2.X*P2.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y;
    if (AbsD(sgn) <= Eps) return 0;
    if (sgn>0){
        for(a=2;a<=Poly0;a++){
            P1 = Poly[a-1];
            P2 = Poly[a];
            if (P1.X*P2.Y+P2.X*P2.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y <= 0) return 0;
        }
    }else{
        for(a=2;a<=Poly0;a++){
            P1 = Poly[a-1];
            P2 = Poly[a];
            if (P1.X*P2.Y+P2.X*P2.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y >= 0) return 0;
        }
    }
    return 1;
}

//determina daca un punct se afla in interiorul unui poligon (punctele de pe laturile poligonului se afla in interiorul acestuia)
int PointInPolygonI(int Poly0, PointI *Poly, PointD &P){
    double sgn;
    int a;
    PointD P1,P2,P3;
    Poly--;
    P1.X = (double)Poly[Poly0].X;
    P1.Y = (double)Poly[Poly0].Y;
    P2.X = (double)Poly[1].X;
    P2.Y = (double)Poly[1].Y;
    P3 = P;
    sgn = P1.X*P2.Y+P2.X*P3.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y;
    for (a=2;AbsD(sgn) <= Eps && a<=Poly0;a++){
        P1.X = (double)Poly[a-1].X;
        P1.Y = (double)Poly[a-1].Y;
        P2.X = (double)Poly[a].X;
        P2.Y = (double)Poly[a].Y;
        sgn = P1.X*P2.Y+P2.X*P3.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y;
    }
    if (sgn>0){
        for(;a<=Poly0;a++){
            P1.X = (double)Poly[a-1].X;
            P1.Y = (double)Poly[a-1].Y;
            P2.X = (double)Poly[a].X;
            P2.Y = (double)Poly[a].Y;
            if (P1.X*P2.Y+P2.X*P3.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y < 0) return 0;
        }
    }else{
        for(;a<=Poly0;a++){
            P1.X = (double)Poly[a-1].X;
            P1.Y = (double)Poly[a-1].Y;
            P2.X = (double)Poly[a].X;
            P2.Y = (double)Poly[a].Y;
            if (P1.X*P2.Y+P2.X*P3.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y > 0) return 0;
        }
    }
    return 1;
}
int PointInPolygonD(int Poly0, PointD *Poly, PointD &P){
    double sgn;
    int a;
    PointD P1,P2,P3;
    Poly--;
    P1 = Poly[Poly0];
    P2 = Poly[1];
    P3 = P;
    sgn = P1.X*P2.Y+P2.X*P3.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y;
    for (a=2;AbsD(sgn) <= Eps && a<=Poly0;a++){
        P1 = Poly[a-1];
        P2 = Poly[a];
        sgn = P1.X*P2.Y+P2.X*P3.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y;
    }
    if (sgn>0){
        for(;a<=Poly0;a++){
            P1 = Poly[a-1];
            P2 = Poly[a];
            if (P1.X*P2.Y+P2.X*P3.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y <-Eps) return 0;
        }
    }else{
        for(;a<=Poly0;a++){
            P1 = Poly[a-1];
            P2 = Poly[a];
            if (P1.X*P2.Y+P2.X*P3.Y+P3.X*P1.Y-P1.X*P3.Y-P2.X*P1.Y-P3.X*P2.Y > Eps) return 0;
        }
    }
    return 1;
}

//calculeaza aria unui triunghi
double ArieTriI(PointI &A, PointI &B, PointI &C){
    return (double)AbsI(A.X*B.Y+B.X*C.Y+C.X*A.Y-A.X*C.Y-B.X*A.Y-C.X*B.Y)/2;
}
double ArieTriD(PointD &A, PointD &B, PointD &C){
    return (double)AbsD(A.X*B.Y+B.X*C.Y+C.X*A.Y-A.X*C.Y-B.X*A.Y-C.X*B.Y)/2;
}

//calculeaza aria unui poligon convex sau cancav
double AriePolyI(int Poly0, PointI *Poly){
    double sol=0;
    int a;
    Poly--;
    for(a=2;a<Poly0;a++){
        sol += Poly[1].X*Poly[a].Y+Poly[a].X*Poly[a+1].Y+Poly[a+1].X*Poly[1].Y-Poly[1].X*Poly[a+1].Y-Poly[a].X*Poly[1].Y-Poly[a+1].X*Poly[a].Y;
    }
    sol = AbsD(sol) / 2;
    return sol;
}
double AriePolyD(int Poly0, PointD *Poly){
    double sol=0;
    int a;
    Poly--;
    for(a=2;a<Poly0;a++){
        sol += Poly[1].X*Poly[a].Y+Poly[a].X*Poly[a+1].Y+Poly[a+1].X*Poly[1].Y-Poly[1].X*Poly[a+1].Y-Poly[a].X*Poly[1].Y-Poly[a+1].X*Poly[a].Y;
    }
    sol = AbsD(sol) / 2;
    return sol;
}

PointP GetPointP(PointD& P) {
    PointP PP;
    PP.dist = sqrt((double)(P.X * P.X + P.Y * P.Y));
    if (P.Y >= 0) {
        PP.alfa = acos(P.X / PP.dist);
    } else {
        PP.alfa = 2 * PI - acos(P.X / PP.dist);
    }
    return PP;
}

PointD mijlocI(PointI A, PointI B) {
	PointD ans;
	ans.X = (A.X + B.X) / 2.0;
	ans.Y = (A.Y + B.Y) / 2.0;
	return ans;
}

LineD PerpendicularaD(LineD L, PointD P) {
	LineD ans;
	ans.A = L.B;
	ans.B = -L.A;
	// ans.A * P.X + ans.B * P.Y + ans.C == 0;
	ans.C = -(ans.A * P.X + ans.B * P.Y);
	return ans;
}

PointD A, B, C;
LineD AB, AC, BC;
double dAB, dAC, dBC;

PointD D;
double R;

double min(double a, double b) {
	return a < b ? a : b;
}

double dist(PointD P) {
	double semn1 = ColD(A, B, P);
	double semn2 = ColD(B, C, P);
	double semn3 = ColD(C, A, P);
	if ((semn1 > 0 && semn2 > 0 && semn3 > 0) ||
			(semn1 < 0 && semn2 < 0 && semn3 < 0)) {
		//printf("%lf %lf %lf %lf %lf\n", P.X, P.Y, DistD(P, AB), DistD(P, AC), DistD(P, BC));
		return min(
				DistD(P, AB),
				min(DistD(P, AC),
				DistD(P, BC)));
	}
	return -1.0;
}

int main(void) {
	FILE *in, *out;
	int i;

	// citirea datelor
	in = fopen("bruiaj.in", "r");
	fscanf(in, "%lf %lf", &A.X, &A.Y);
	fscanf(in, "%lf %lf", &B.X, &B.Y);
	fscanf(in, "%lf %lf", &C.X, &C.Y);
	fclose(in);

	// calcularea solutiei
	AB = DreaptaD(A, B);
	AC = DreaptaD(A, C);
	BC = DreaptaD(B, C);

	D.X = (A.X + B.X + C.X) / 3.0;
	D.Y = (A.Y + B.Y + C.Y) / 3.0;

	double err = 1000.0;
	PointD newP;
	double d;
	double solD;
	int solI;
	double alpha;
	for (; err > 1e-10; ) {
		solD = dist(D);
		solI = -1;
		//printf("%lf %lf %lf %lf\n", err, D.X, D.Y, solD);
		bool improved = false;
		double alpha;
		for (i = 0; i < 40; ++i) {
			alpha = rand() / (double)(1 << 15) * (2 * PI);
			newP.X = D.X + err * sin(alpha);
			newP.Y = D.Y + err * cos(alpha);
			d = dist(newP);
			if (solD < d) {
				D = newP;
				improved = true;
				break;
			}
		}
		if (!improved) {
			err *= 9.0 / 10.0;
		}
	}
	R = DistD(D, AB);

	// afisarea solutiei
	out = fopen("bruiaj.out", "w");
	fprintf(out, "%lf %lf\n", D.X, D.Y);
	fprintf(out, "%lf\n", R);
	fclose(out);
	return 0;
}
