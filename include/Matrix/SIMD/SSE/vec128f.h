/**************************************
SSE x4 float. 32-bit x 4 = 128 bits
**************************************/
#define NBITS 32 //variable bits
#define NVARS 4  //size of vector

class vec128f
{
	public:
		__m128 __attribute__((aligned(NBITS))) v; //packed vector register (of aligned 32-bit floats)
	public:
		vec128f() { v = _mm_setzero_ps(); }
		vec128f(float f) { v = _mm_set1_ps(f); }
		vec128f(float f0,float f1,float f2,float f3) { v = _mm_setr_ps(f0,f1,f2,f3); }
		vec128f(__m128 const& x) { v = x; }
		
		inline void insert(int index, float value) { v[index]=value; }
		inline const float operator [] (const int& index) const { return v[index]; } //getter
		inline float& operator [] (const int& index) { return v[index]; } //setter
};


//Operators:
static inline vec128f  operator +  (vec128f const &a, vec128f const &b) { return _mm_add_ps(a.v,b.v); }
static inline vec128f  operator +  (vec128f const &a, float b)          { return _mm_add_ps(a.v,_mm_set1_ps(b)); }
static inline vec128f& operator += (vec128f &a, vec128f const &b)       { a=a+b; return a; }
static inline vec128f  operator -  (vec128f const &a, vec128f const &b) { return _mm_sub_ps(a.v,b.v); }
static inline vec128f  operator -  (vec128f const &a, float b)          { return _mm_sub_ps(a.v,_mm_set1_ps(b)); }
static inline vec128f& operator -= (vec128f &a, vec128f const &b)       { a=a-b; return a; }
static inline vec128f  operator *  (vec128f const &a, vec128f const &b) { return _mm_mul_ps(a.v,b.v); }
static inline vec128f  operator *  (vec128f const &a, float b)          { return _mm_mul_ps(a.v,_mm_set1_ps(b)); }
static inline vec128f& operator *= (vec128f &a, vec128f const &b)       { a=a*b; return a; }
static inline vec128f  operator /  (vec128f const &a, vec128f const &b) { return _mm_div_ps(a.v,b.v); }
static inline vec128f  operator /  (vec128f const &a, float b)          { return _mm_div_ps(a.v,_mm_set1_ps(b)); }
static inline vec128f& operator /= (vec128f &a, vec128f const &b)       { a=a/b; return a; }

static inline vec128f  operator -  (vec128f const &a) { return _mm_sub_ps(_mm_setzero_ps(),a.v); }
static inline vec128f& operator ++ (vec128f &a) { a = a + 1; return a;}
static inline vec128f  operator ++ (vec128f &a,int) { vec128f __attribute__((aligned(NBITS))) a0(a); a=a+1; return a0; }
static inline vec128f& operator -- (vec128f &a) { a = a - 1; return a;}
static inline vec128f  operator -- (vec128f &a,int) { vec128f __attribute__((aligned(NBITS))) a0=a; a=a-1; return a0; }

static inline vec128f operator == (vec128f const &a,vec128f const &b) { return _mm_cmp_ps(a.v,b.v,0); }
static inline vec128f operator != (vec128f const &a,vec128f const &b) { return _mm_cmp_ps(a.v,b.v,4); }
static inline vec128f operator <  (vec128f const &a,vec128f const &b) { return _mm_cmp_ps(a.v,b.v,1); }
static inline vec128f operator >  (vec128f const &a,vec128f const &b) { return _mm_cmp_ps(b.v,a.v,1); }
static inline vec128f operator <= (vec128f const &a,vec128f const &b) { return _mm_cmp_ps(a.v,b.v,2); }
static inline vec128f operator >= (vec128f const &a,vec128f const &b) { return _mm_cmp_ps(b.v,a.v,2); }

static inline vec128f operator !  (vec128f const &a) { return _mm_cmp_ps(a.v,_mm_setzero_ps(),0); }
static inline vec128f operator &  (vec128f const &a,vec128f const &b) { return _mm_and_ps(a.v,b.v); }
static inline vec128f operator && (vec128f const &a,vec128f const &b) { return _mm_and_ps(a.v,b.v); }
static inline vec128f operator |  (vec128f const &a,vec128f const &b) { return _mm_or_ps(a.v,b.v); }
static inline vec128f operator || (vec128f const &a,vec128f const &b) { return _mm_or_ps(a.v,b.v); }
static inline vec128f operator ^  (vec128f const &a,vec128f const &b) { return _mm_xor_ps(a.v,b.v); }

static inline vec128f operator % (vec128f const &a,vec128f const &b)
{
	__m128 __attribute__((aligned(NBITS))) c = _mm_div_ps(a.v,b.v); //Slow due to division
	__m128 __attribute__((aligned(NBITS))) base = _mm_mul_ps(_mm_round_ps(c,3+NBITS),b.v);
	return _mm_sub_ps(a.v, base);
}
static inline vec128f operator % (vec128f const &a,float b)
{
	__m128 __attribute__((aligned(NBITS))) den = _mm_set1_ps(b);
	__m128 __attribute__((aligned(NBITS))) c = _mm_div_ps(a.v,den); //Slow due to division
	__m128 __attribute__((aligned(NBITS))) base = _mm_mul_ps(_mm_round_ps(c,3+NBITS),den);
	return _mm_sub_ps(a.v, base);
}

//Functions:
static inline vec128f max(vec128f const &a,vec128f const &b) { return _mm_max_ps(a.v,b.v); }
static inline vec128f min(vec128f const &a,vec128f const &b) { return _mm_min_ps(a.v,b.v); }
static inline vec128f sqrt(vec128f const &a) { return _mm_sqrt_ps(a.v); }
static inline vec128f round(vec128f const &a)    { return _mm_round_ps(a.v,_MM_FROUND_TO_NEAREST_INT); } // function round:    round to nearest integer (even). (result as float vector)
static inline vec128f floor(vec128f const &a)    { return _mm_round_ps(a.v,_MM_FROUND_TO_NEG_INF);     } // function floor:    round towards minus infinity. (result as float vector)
static inline vec128f ceil(vec128f const &a)     { return _mm_round_ps(a.v,_MM_FROUND_TO_POS_INF);     } // function ceil:     round towards plus infinity. (result as float vector)
static inline vec128f truncate(vec128f const &a) { return _mm_round_ps(a.v,_MM_FROUND_TO_ZERO);        } // function truncate: round towards zero. (result as float vector)
//static inline v8f abs(v8f const &a)
//{ 
//	__m256 __attribute__((aligned(32))) mask = constant8f<0x7FFFFFFF>();
//	return _mm256_and_ps(a.v,mask);
//}
//
//static inline vec128f infinite8f() {return constant8f<0x7F800000>();}
//static inline vec128f nan8f(int n = 0x10) {return _mm256_castsi256_ps(_mm256_set1_epi32(0x7FC00000 + n));}

//IO:
static inline std::ostream& operator << (std::ostream& output, const vec128f& x){ output << "vec128f: ["; for(int i=0;i<NVARS-1;++i) output << x[i] << ","; output << x[NVARS-1] << "]"; return output; }



/*************************************************
compiler:  -m32 -msse4.1  to use _mm_round_ps()
*************************************************/
