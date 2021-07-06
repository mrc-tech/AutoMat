/**************************************
AVX x8 float. 32-bit x 8 = 256 bits
**************************************/
#define NBITS 32 //variable bits
#define NVARS 8  //size of vector

class vec256f
{
	public:
		__m256 __attribute__((aligned(NBITS))) v; //packed vector register (of aligned 32-bit floats)
	public:
		vec256f() { v = _mm256_setzero_ps(); }
		vec256f(float f) { v = _mm256_set1_ps(f); }
		vec256f(float f0,float f1,float f2,float f3,float f4,float f5,float f6,float f7) { v = _mm256_setr_ps(f0,f1,f2,f3,f4,f5,f6,f7); }
		vec256f(__m256 const& x) { v = x; }
		
		inline void insert(int index, float value) { v[index]=value; }
		inline float operator [] (int index) const { return v[index]; }
};


//Operators:
static inline vec256f  operator +  (vec256f const &a, vec256f const &b) { return _mm256_add_ps(a.v,b.v); }
static inline vec256f  operator +  (vec256f const &a, float b)          { return _mm256_add_ps(a.v,_mm256_set1_ps(b)); }
static inline vec256f& operator += (vec256f &a, vec256f const &b)       { a=a+b; return a; }
static inline vec256f  operator -  (vec256f const &a, vec256f const &b) { return _mm256_sub_ps(a.v,b.v); }
static inline vec256f  operator -  (vec256f const &a, float b)          { return _mm256_sub_ps(a.v,_mm256_set1_ps(b)); }
static inline vec256f& operator -= (vec256f &a, vec256f const &b)       { a=a-b; return a; }
static inline vec256f  operator *  (vec256f const &a, vec256f const &b) { return _mm256_mul_ps(a.v,b.v); }
static inline vec256f  operator *  (vec256f const &a, float b)          { return _mm256_mul_ps(a.v,_mm256_set1_ps(b)); }
static inline vec256f& operator *= (vec256f &a, vec256f const &b)       { a=a*b; return a; }
static inline vec256f  operator /  (vec256f const &a, vec256f const &b) { return _mm256_div_ps(a.v,b.v); }
static inline vec256f  operator /  (vec256f const &a, float b)          { return _mm256_div_ps(a.v,_mm256_set1_ps(b)); }
static inline vec256f& operator /= (vec256f &a, vec256f const &b)       { a=a/b; return a; }

static inline vec256f  operator -  (vec256f const &a) { return _mm256_sub_ps(_mm256_setzero_ps(),a.v); }
static inline vec256f& operator ++ (vec256f &a) { a = a + 1; return a;}
static inline vec256f  operator ++ (vec256f &a,int) { vec256f __attribute__((aligned(NBITS))) a0(a); a=a+1; return a0; }
static inline vec256f& operator -- (vec256f &a) { a = a - 1; return a;}
static inline vec256f  operator -- (vec256f &a,int) { vec256f __attribute__((aligned(NBITS))) a0=a; a=a-1; return a0; }

static inline vec256f operator == (vec256f const &a,vec256f const &b) { return _mm256_cmp_ps(a.v,b.v,0); }
static inline vec256f operator != (vec256f const &a,vec256f const &b) { return _mm256_cmp_ps(a.v,b.v,4); }
static inline vec256f operator <  (vec256f const &a,vec256f const &b) { return _mm256_cmp_ps(a.v,b.v,1); }
static inline vec256f operator >  (vec256f const &a,vec256f const &b) { return _mm256_cmp_ps(b.v,a.v,1); }
static inline vec256f operator <= (vec256f const &a,vec256f const &b) { return _mm256_cmp_ps(a.v,b.v,2); }
static inline vec256f operator >= (vec256f const &a,vec256f const &b) { return _mm256_cmp_ps(b.v,a.v,2); }

static inline vec256f operator !  (vec256f const &a) { return _mm256_cmp_ps(a.v,_mm256_setzero_ps(),0); }
static inline vec256f operator &  (vec256f const &a,vec256f const &b) { return _mm256_and_ps(a.v,b.v); }
static inline vec256f operator && (vec256f const &a,vec256f const &b) { return _mm256_and_ps(a.v,b.v); }
static inline vec256f operator |  (vec256f const &a,vec256f const &b) { return _mm256_or_ps(a.v,b.v); }
static inline vec256f operator || (vec256f const &a,vec256f const &b) { return _mm256_or_ps(a.v,b.v); }
static inline vec256f operator ^  (vec256f const &a,vec256f const &b) { return _mm256_xor_ps(a.v,b.v); }

static inline vec256f operator % (vec256f const &a,vec256f const &b)
{
	__m256 __attribute__((aligned(NBITS))) c = _mm256_div_ps(a.v,b.v); //Slow due to division
	__m256 __attribute__((aligned(NBITS))) base = _mm256_mul_ps(_mm256_round_ps(c,3+8),b.v);
	return _mm256_sub_ps(a.v, base);
}
static inline vec256f operator % (vec256f const &a,float b)
{
	__m256 __attribute__((aligned(NBITS))) den = _mm256_set1_ps(b);
	__m256 __attribute__((aligned(NBITS))) c = _mm256_div_ps(a.v,den); //Slow due to division
	__m256 __attribute__((aligned(NBITS))) base = _mm256_mul_ps(_mm256_round_ps(c,3+8),den);
	return _mm256_sub_ps(a.v, base);
}

//Functions:
static inline vec256f max(vec256f const &a,vec256f const &b) { return _mm256_max_ps(a.v,b.v); }
static inline vec256f min(vec256f const &a,vec256f const &b) { return _mm256_min_ps(a.v,b.v); }
static inline vec256f sqrt(vec256f const &a) { return _mm256_sqrt_ps(a.v); }
static inline vec256f round(vec256f const &a)    { return _mm256_round_ps(a.v,0+8); } // function round:    round to nearest integer (even). (result as float vector)
static inline vec256f floor(vec256f const &a)    { return _mm256_round_ps(a.v,1+8); } // function floor:    round towards minus infinity. (result as float vector)
static inline vec256f ceil(vec256f const &a)     { return _mm256_round_ps(a.v,2+8); } // function ceil:     round towards plus infinity. (result as float vector)
static inline vec256f truncate(vec256f const &a) { return _mm256_round_ps(a.v,3+8); } // function truncate: round towards zero. (result as float vector)
//static inline v8f abs(v8f const &a)
//{ 
//	__m256 __attribute__((aligned(32))) mask = constant8f<0x7FFFFFFF>();
//	return _mm256_and_ps(a.v,mask);
//}
//
//static inline vec256f infinite8f() {return constant8f<0x7F800000>();}
//static inline vec256f nan8f(int n = 0x10) {return _mm256_castsi256_ps(_mm256_set1_epi32(0x7FC00000 + n));}

//IO:
static inline std::ostream& operator << (std::ostream& output, const vec256f& x){ output << "vec256f: ["; for(int i=0;i<NVARS;++i) output << x[i] << ","; output << "]"; return output; }

