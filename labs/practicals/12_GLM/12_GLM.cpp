#include <glm\glm.hpp>
#include <glm\gtc\constants.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\quaternion.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtx\projection.hpp>
#include <iostream>

using namespace std;
using namespace glm;

int main() 
{
	// GLM VECTORS

	/*

	BASICS
	
	Add six new variables to the main application for this lesson.

	*/

	// note, these are contructors ie. we are creating vector OBJECTS
	vec2 u(1.0, 0.0);
	vec2 a(0.0, 1.0);

	vec3 v(0.0, 1.0, 0.0);
	vec3 b(1.0, 0.0, 0.0);

	vec4 w(0.0, 0.0, 1.0, 0.0);
	vec4 c(0.0, 1.0, 0.0, 0.0);

	/*
	
	Create another six variables. Convert one of the 2D vectors to a 3D and
	one to a 4D. Then convert one of the 3D vectors to a 2D and one to a 4D. Finally,
	convert one of the 4D vectors to a 2D and one to a 3D.
	
	*/

	// two 2d vectors
	vec2 d(1.0, 0.0);
	vec2 e(0.0, 1.0);

	// convert one of the 2d to 3d and another one to 4d
	vec3 f(d, 0.0);
	vec4 g(e, 0.0, 0.0);

	// convert the conversions further on
	vec2 h(f);
	vec4 i(f, 0.0);

	vec2 j(g);
	vec3 k(g);

	/*
	
	Create another six variables. Convert one of the 2D vectors to a 3D and
	one to a 4D. Then convert one of the 3D vectors to a 2D and one to a 4D. Finally,
	convert one of the 4D vectors to a 2D and one to a 3D

	SKIPPED

	*/

	/*
	
	OVERLOADED

	Again, you want to create six more variables. Add two of your 2D vectors
	together storing the result, and subtract one from another again storing the result. Do
	the same for 3D and 4D vectors.
	*/

	vec2 jesus(1.0, 0.0);
	vec2 christ(0.0, 1.0);

	vec2 riseFromDeath = jesus + christ;
	vec2 dieOnTheCross = jesus - christ;

	// SKIPPED REST

	/*
	
	Six more vector variables need to be added to your application again. This
	time, multiply a 2D vector by a scalar value (float) storing the result, and the same
	for division. Do the same for 3D and 4D vectors.

	*/

	vec2 so(1.0, 0.0);
	vec2 done(0.0, 1.0);

	so *= 2;
	done *= 5;

	/*

	GLM FUNCTIONS 
	
	Now create three float values and get the length of three of your defined
	vectors - a 2D one, a 3D one and a 4D one.

	*/

	vec2 lets(4.0, 0.0);
	vec3 find(0.0, 2.0, 0.0);
	vec4 lengths(0.0, 1.0, 2.0, 0.0);

	float letsLength = length(lets);
	float findLength = length(find);
	float lengthsLength = length(lengths);

	/*
	
	Create three variables and store the result of normalizing a 2D, 3D, and
	4D vector.

	*/

	vec2 normalLets = normalize(lets);
	vec3 normalFind = normalize(find);
	vec4 normalLengths = normalize(lengths);

	/*
	
	Again you need three new float variables. Get the result of the dot product
	of a 2D, 3D, and 4D vector and store the results.
	*/

	float dotProdLetsAndFind = dot(lets, vec2(find));

	/*
	
	Perform three projection operations, storing the result. Project a 2D vector
	onto another 2D vector, and likewise for 3D and 4D vectors.
	SKIPPED

	*/
	vec2 second(0.0, 1.0);
	vec2 projection = proj(jesus, second);

	/*
	
	The cross product of 3D vectors is the only interesting one in our work.
	Perform a cross product on two of the 3D vectors you have previously defined, storing
	the result.
	
	*/

	vec3 one(1.0f, 0.0f, 0.0f);
	vec3 two(2.0f, 0.0f, 0.0f);

	vec3 crossProduct = cross(one, two);

	// GLM MATRICES

	// example and identity matrix
	mat4 m(1.0f);

	/*
	
	Create a few matrices. You can take a look at the attributes of the matrix
	and see how you can access (get and set) individual components - just as vectors. Do
	this as well to get a feel for the individual types.
	
	*/

	mat4 hello(2.0f);
	mat4 world(1.0f);

	float theYofSecond = world.y;

	/*
	
	Add and subtract some matrices, storing the results.
	
	*/

	mat4 addMatrix = hello + world;
	mat4 subMatrix = world - hello;

	/*
	
	Scale some of your defined matrices, storing the results.

	*/

	mat4 scaledMatrix = 2.0f * hello;
	mat4 anoterScaledMatrix = 6.0f * world;

	/*
	
	Multiply some matrices together. Remember that only certain sizes of
	matrices can be multiplied together. Try and multiply some of the different types
	together and see what GLM can do.
	*/

	mat4 multipliedMatrices = hello * world;
	mat4 anotherMultiMatrix = mat3x4(2.0f) * mat4x3(1.0f);


	/*
	
	Create a translation matrix. Then transform one of your 3D vectors (using
	the technique shown to allow the multiplication), storing the result in another 3D
	vector. Check your result to ensure that you have done this correctly.

	*/

	// first what is to be translated, second the tranlation matrix!!!
	vec3 translateMatrix(1, 2, 3);
	mat4 translatedMatrix = translate(mat4(1.0f), translateMatrix);

	/*
	
	Create three rotation matrices - one for each rotation type. Sensible rotations
	here are for quarter–rotations (e.g. pi/2 radians). Then transform some 3D vectors
	- preferably ones pointing down an axis (e.g. (1, 0, 0)) so you can check the result.
	Finally, combine the rotations, by multiplying them together, then perform a transformation
	and again check the result.

	*/

	vec3 rotateMatrix(0.0f, 1.0f, 0.0f);
	mat4 rotatedMatrix = rotate(mat4(2.0f), 90.0f, rotateMatrix);


	/*
	
	Create a scale matrix and then transform a 3D vector with this matrix

	*/

	vec3 scaleMatrix(2, 3, 0);
	mat4 scaledMatrix = scale(mat4(1.0f), scaleMatrix);

	/*
	
	Combine three of your transformation matrices together. Then transform
	a 3D vector by this combination, storing your result. You should be able to check that
	you have the right result.
	
	*/

	vec3 combinedTrans = (translateMatrix * (rotateMatrix * scaleMatrix));	vec3 combinedTransResult = vec3(1, 2, 3) * combinedTrans;

	// QUOTERNIONS

	/*
	
	Create a quaternion in the project for this lesson
	
	*/

	quat thisQuat;

	/*
	
	Create quaternions that represent rotations around the three main axes.
	
	*/

	quat qx = rotate(quat(), 25.0f, vec3(1.0f, 0.0f, 0.0f));
	quat qy = rotate(quat(), 30.0f, vec3(0.0f, 1.0f, 0.0f));
	quat qz = rotate(quat(), 35.0f, vec3(0.0f, 0.0f, 1.0f));

	quat R = qx * qy * qz;

	/*
	
	Convert your combined rotation quaternion to a matrix, and then use it to
	transform a 3D vector, storing the result.
	*/

	mat4 castedQuat = mat4_cast(R);
}