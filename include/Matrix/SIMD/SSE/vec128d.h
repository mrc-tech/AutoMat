/**************************************
SSE x2 double. 64-bit x 2 = 128 bits
**************************************/
#define NBITS 64 //variable bits
#define NVARS 2  //size of vector

class vec128d
{
	public:
		__m128d __attribute__((aligned(NBITS))) v; //packed vector register (of aligned 32-bit floats)
	public:
		vec128d() { v = _mm_setzero_pd(); }
		vec128d(double d) { v = _mm_set1_pd(d); }
		vec128d(double d0, double d1) { v = _mm_setr_pd(d0,d1); }
		vec128d(__m128d const& x) { v = x; }
		
		inline void insert(int index, float value) { v[index]=value; }
		inline float operator [] (int index) const { return v[index]; }
};


//Operators:
static inline vec128d  operator +  (vec128d const &a, vec128d const &b) { return _mm_add_pd(a.v,b.v); }
static inline vec128d  operator +  (vec128d const &a, double b)         { return _mm_add_pd(a.v,_mm_set1_pd(b)); }
static inline vec128d& operator += (vec128d &a, vec128d const &b)       { a=a+b; return a; }
static inline vec128d  operator -  (vec128d const &a, vec128d const &b) { return _mm_sub_pd(a.v,b.v); }
static inline vec128d  operator -  (vec128d const &a, double b)         { return _mm_sub_pd(a.v,_mm_set1_pd(b)); }
static inline vec128d& operator -= (vec128d &a, vec128d const &b)       { a=a-b; return a; }
static inline vec128d  operator *  (vec128d const &a, vec128d const &b) { return _mm_mul_pd(a.v,b.v); }
static inline vec128d  operator *  (vec128d const &a, double b)          { return _mm_mul_pd(a.v,_mm_set1_pd(b)); }
static inline vec128d& operator *= (vec128d &a, vec128d const &b)       { a=a*b; return a; }
static inline vec128d  operator /  (vec128d const &a, vec128d const &b) { return _mm_div_pd(a.v,b.v); }
static inline vec128d  operator /  (vec128d const &a, double b)         { return _mm_div_pd(a.v,_mm_set1_pd(b)); }
static inline vec128d& operator /= (vec128d &a, vec128d const &b)       { a=a/b; return a; }

static inline vec128d  operator -  (vec128d const &a) { return _mm_sub_pd(_mm_setzero_pd(),a.v); }
static inline vec128d& operator ++ (vec128d &a) { a = a + 1; return a;}
static inline vec128d  operator ++ (vec128d &a,int) { vec128d __attribute__((aligned(NBITS))) a0(a); a=a+1; return a0; }
static inline vec128d& operator -- (vec128d &a) { a = a - 1; return a;}
static inline vec128d  operator -- (vec128d &a,int) { vec128d __attribute__((aligned(NBITS))) a0=a; a=a-1; return a0; }

static inline vec128d operator == (vec128d const &a,vec128d const &b) { return _mm_cmp_pd(a.v,b.v,0); }
static inline vec128d operator != (vec128d const &a,vec128d const &b) { return _mm_cmp_pd(a.v,b.v,4); }
static inline vec128d operator <  (vec128d const &a,vec128d const &b) { return _mm_cmp_pd(a.v,b.v,1); }
static inline vec128d operator >  (vec128d const &a,vec128d const &b) { return _mm_cmp_pd(b.v,a.v,1); }
static inline vec128d operator <= (vec128d const &a,vec128d const &b) { return _mm_cmp_pd(a.v,b.v,2); }
static inline vec128d operator >= (vec128d const &a,vec128d const &b) { return _mm_cmp_pd(b.v,a.v,2); }

static inline vec128d operator !  (vec128d const &a) { return _mm_cmp_pd(a.v,_mm_setzero_pd(),0); }
static inline vec128d operator &  (vec128d const &a,vec128d const &b) { return _mm_and_pd(a.v,b.v); }
static inline vec128d operator && (vec128d const &a,vec128d const &b) { return _mm_and_pd(a.v,b.v); }
static inline vec128d operator |  (vec128d const &a,vec128d const &b) { return _mm_or_pd(a.v,b.v); }
static inline vec128d operator || (vec128d const &a,vec128d const &b) { return _mm_or_pd(a.v,b.v); }
static inline vec128d operator ^  (vec128d const &a,vec128d const &b) { return _mm_xor_pd(a.v,b.v); }

static inline vec128d operator % (vec128d const &a,vec128d const &b)
{
	__m128d __attribute__((aligned(NBITS))) c = _mm_div_pd(a.v,b.v); //Slow due to division
	__m128d __attribute__((aligned(NBITS))) base = _mm_mul_pd(_mm_round_pd(c,3+NBITS),b.v);
	return _mm_sub_pd(a.v, base);
}
static inline vec128d operator % (vec128d const &a,double b)
{
	__m128d __attribute__((aligned(NBITS))) den = _mm_set1_pd(b);
	__m128d __attribute__((aligned(NBITS))) c = _mm_div_pd(a.v,den); //Slow due to division
	__m128d __attribute__((aligned(NBITS))) base = _mm_mul_pd(_mm_round_pd(c,3+NBITS),den);
	return _mm_sub_pd(a.v, base);
}

//Functions:
static inline vec128d max(vec128d const &a,vec128d const &b) { return _mm_max_pd(a.v,b.v); }
static inline vec128d min(vec128d const &a,vec128d const &b) { return _mm_min_pd(a.v,b.v); }
static inline vec128d sqrt(vec128d const &a) { return _mm_sqrt_pd(a.v); }
static inline vec128d round(vec128d const &a)    { return _mm_round_pd(a.v,_MM_FROUND_TO_NEAREST_INT); } // function round:    round to nearest integer (even). (result as float vector)
static inline vec128d floor(vec128d const &a)    { return _mm_round_pd(a.v,_MM_FROUND_TO_NEG_INF);     } // function floor:    round towards minus infinity. (result as float vector)
static inline vec128d ceil(vec128d const &a)     { return _mm_round_pd(a.v,_MM_FROUND_TO_POS_INF);     } // function ceil:     round towards plus infinity. (result as float vector)
static inline vec128d truncate(vec128d const &a) { return _mm_round_pd(a.v,_MM_FROUND_TO_ZERO);        } // function truncate: round towards zero. (result as float vector)
//static inline v8f abs(v8f const &a)
//{ 
//	__m256 __attribute__((aligned(32))) mask = constant8f<0x7FFFFFFF>();
//	return _mm256_and_ps(a.v,mask);
//}
//
//static inline vec128d infinite8f() {return constant8f<0x7F800000>();}
//static inline vec128d nan8f(int n = 0x10) {return _mm256_castsi256_ps(_mm256_set1_epi32(0x7FC00000 + n));}

//IO:
static inline std::ostream& operator << (std::ostream& output, const vec128d& x){ output << "vec128d: ["; for(int i=0;i<NVARS-1;++i) output << x[i] << ","; output << x[NVARS-1] << "]"; return output; }



/*************************************************
compiler:  -m32 -msse4.1  to use _mm_round_ps()
*************************************************/
