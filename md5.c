#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/* MD5 context structure */
typedef struct {
    uint32_t state[4];
    uint32_t count[2];
    unsigned char buffer[64];
} MD5_CTX;

/* MD5 Constants */
static const uint32_t md5_constants[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
    0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
    0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
    0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
    0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
    0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
    0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
    0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
    0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
    0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
    0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static const uint32_t shifts[64] = {
    7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
    5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
    4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
    6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21
};

static const uint32_t indices[64] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12,
    5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2,
    0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9
};

/* Helper macros */
#define F(x, y, z) (((x) & (y)) | ((~(x)) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~(z))))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~(z))))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define FF(a, b, c, d, x, s, ac) \
    (a) += F((b), (c), (d)) + (x) + (ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b);

#define GG(a, b, c, d, x, s, ac) \
    (a) += G((b), (c), (d)) + (x) + (ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b);

#define HH(a, b, c, d, x, s, ac) \
    (a) += H((b), (c), (d)) + (x) + (ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b);

#define II(a, b, c, d, x, s, ac) \
    (a) += I((b), (c), (d)) + (x) + (ac); \
    (a) = ROTATE_LEFT((a), (s)); \
    (a) += (b);

/* Initialize MD5 context */
void MD5_Init(MD5_CTX *ctx) {
    ctx->count[0] = ctx->count[1] = 0;
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xefcdab89;
    ctx->state[2] = 0x98badcfe;
    ctx->state[3] = 0x10325476;
}

/* Process a single 512-bit block */
static void MD5_Transform(uint32_t state[4], const unsigned char block[64]) {
    uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
    uint32_t x[16];
    int i;

    /* Decode input (little endian) */
    for (i = 0; i < 16; i++) {
        x[i] = block[i*4] | (block[i*4+1] << 8) |
               (block[i*4+2] << 16) | (block[i*4+3] << 24);
    }

    /* Round 1 */
    for (i = 0; i < 16; i++) {
        uint32_t f = F(b, c, d);
        uint32_t k = md5_constants[i];
        uint32_t xval = x[i];
        uint32_t t = a + f + k + xval;
        t = ROTATE_LEFT(t, shifts[i]);
        a = d; d = c; c = b; b = b + t;
    }

    /* Round 2 */
    for (i = 16; i < 32; i++) {
        int idx = indices[i];
        uint32_t f = G(b, c, d);
        uint32_t k = md5_constants[i];
        uint32_t xval = x[idx];
        uint32_t t = a + f + k + xval;
        t = ROTATE_LEFT(t, shifts[i]);
        a = d; d = c; c = b; b = b + t;
    }

    /* Round 3 */
    for (i = 32; i < 48; i++) {
        int idx = indices[i];
        uint32_t f = H(b, c, d);
        uint32_t k = md5_constants[i];
        uint32_t xval = x[idx];
        uint32_t t = a + f + k + xval;
        t = ROTATE_LEFT(t, shifts[i]);
        a = d; d = c; c = b; b = b + t;
    }

    /* Round 4 */
    for (i = 48; i < 64; i++) {
        int idx = indices[i];
        uint32_t f = I(b, c, d);
        uint32_t k = md5_constants[i];
        uint32_t xval = x[idx];
        uint32_t t = a + f + k + xval;
        t = ROTATE_LEFT(t, shifts[i]);
        a = d; d = c; c = b; b = b + t;
    }

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

/* Update MD5 with new data */
void MD5_Update(MD5_CTX *ctx, const unsigned char *input, uint32_t len) {
    uint32_t index = (ctx->count[0] >> 3) & 0x3f;
    uint32_t inputlen = len << 3;
    uint32_t partlen = 64 - index;
    uint32_t i = 0;

    ctx->count[0] += inputlen;
    if (ctx->count[0] < inputlen)
        ctx->count[1]++;
    ctx->count[1] += (len >> 29);

    if (len >= partlen) {
        memcpy(&ctx->buffer[index], input, partlen);
        MD5_Transform(ctx->state, ctx->buffer);

        for (i = partlen; i + 63 < len; i += 64) {
            MD5_Transform(ctx->state, &input[i]);
        }
        index = 0;
    } else {
        i = 0;
    }

    memcpy(&ctx->buffer[index], &input[i], len - i);
}

/* Finalize MD5 and produce digest */
void MD5_Final(unsigned char digest[16], MD5_CTX *ctx) {
    unsigned char bits[8];
    uint32_t index = (ctx->count[0] >> 3) & 0x3f;
    uint32_t padlen = (index < 56) ? (56 - index) : (120 - index);
    static unsigned char padding[64] = {0x80};
    int i;

    /* Encode length */
    for (i = 0; i < 4; i++) {
        bits[i] = (ctx->count[0] >> (i * 8)) & 0xff;
        bits[i + 4] = (ctx->count[1] >> (i * 8)) & 0xff;
    }

    /* Padding */
    MD5_Update(ctx, padding, padlen);
    MD5_Update(ctx, bits, 8);

    /* Produce output */
    for (i = 0; i < 4; i++) {
        digest[i*4] = (ctx->state[i]) & 0xff;
        digest[i*4+1] = (ctx->state[i] >> 8) & 0xff;
        digest[i*4+2] = (ctx->state[i] >> 16) & 0xff;
        digest[i*4+3] = (ctx->state[i] >> 24) & 0xff;
    }
}

/* Calculate MD5 for a file */
int calculate_file_md5(const char *filename, char *md5_string) {
    FILE *fp;
    MD5_CTX ctx;
    unsigned char buffer[4096];
    size_t bytes;
    unsigned char digest[16];
    int i;

    fp = fopen(filename, "rb");
    if (!fp) {
        return 0;
    }

    MD5_Init(&ctx);

    while ((bytes = fread(buffer, 1, sizeof(buffer), fp)) > 0) {
        MD5_Update(&ctx, buffer, bytes);
    }

    fclose(fp);

    MD5_Final(digest, &ctx);

    /* Convert to hex string */
    for (i = 0; i < 16; i++) {
        sprintf(&md5_string[i*2], "%02x", digest[i]);
    }
    md5_string[32] = '\0';

    return 1;
}

/* Get simplified filename from path */
static const char* get_filename(const char *path) {
    const char *filename = path;
    const char *sep = NULL;
    int i;
    
    /* Find the last path separator (Windows and Unix) */
    for (i = 0; path[i]; i++) {
        if (path[i] == '\\' || path[i] == '/') {
            sep = &path[i];
        }
    }
    
    /* Return filename if separator found, otherwise return the whole path */
    if (sep) {
        filename = sep + 1;
    }
    
    return filename;
}

/* Truncate filename if too long, returns length of display string */
static int format_display_name(const char *path, char *display, int max_len) {
    const char *filename = get_filename(path);
    int len = strlen(filename);
    
    if (len > max_len) {
        /* Truncate and add "..." prefix */
        int truncate_len = max_len - 3;
        strcpy(display, "...");
        strncpy(&display[3], &filename[len - truncate_len], truncate_len);
        display[max_len] = '\0';
        return max_len;
    } else {
        strcpy(display, filename);
        return len;
    }
}

int main(int argc, char *argv[]) {
    char md5_string[33];
    char display_name[41];  /* Extra space for null terminator */
    const int max_filename_width = 40;
    const int column_width = 42; /* Total width for filename column */
    int i;

    if (argc < 2) {
        printf("Usage: %s file1 [file2 ...]\n", argv[0]);
        return 1;
    }
    
    /* Print table header */
    printf("%-*s %s\n", column_width, "Filename", "MD5");
    printf("%.*s %.*s\n", column_width, "===========================================", 
           32, "================================");
    
    for (i = 1; i < argc; i++) {
        format_display_name(argv[i], display_name, max_filename_width);
        
        if (calculate_file_md5(argv[i], md5_string)) {
            printf("%-*s %s\n", column_width, display_name, md5_string);
        } else {
            printf("%-*s %s\n", column_width, display_name, "ERROR: Cannot open file");
        }
    }
    
    return 0;
}
