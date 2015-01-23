struct point3d;

bool operator==(point3d, point3d);
bool operator!=(point3d, point3d);

float distance(point3d, point3d);
float squared_distance(point3d, point3d);

// ============================================================================

struct vector3d;

vector3d operator-(vector3d);
vector3d operator-(vector3d, vector3d);
vector3d operator+(vector3d, vector3d);

bool operator==(vector3d, vector3d);
bool operator!=(vector3d, vector3d);

float lenght(vector3d);
float squared_lenght(vector3d);

vector3d normalized(vector3d);
vector3d scaled(vector3d, float);

vector3d cross(vector3d, vector3d);
float dot(vector3d, vector3d);

// ============================================================================

struct matrix4x4;

matrix4x4 operator-(matrix4x4, matrix4x4);
matrix4x4 operator+(matrix4x4, matrix4x4);

bool operator==(matrix4x4, matrix4x4);
bool operator!=(matrix4x4, matrix4x4);

boost::optional<matrix4x4> inversed_safe(matrix4x4); // Works for non-inversable matrix

matrix4x4 transposed(matrix4x4);
matrix4x4 inversed(matrix4x4);

matrix4x4 multiply(matrix4x4, matrix4x4);