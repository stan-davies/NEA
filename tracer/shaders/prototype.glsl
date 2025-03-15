/******************************************************************************
 *
 *   prototypes for: `main.glsl`
 *
 *****************************************************************************/

/*
 *   PARAMS : Ray that is bouncing. Colour attentuation from bounce. Boolean
 *            indicating whether or not to break the loop. Boolean indicating
 *            whether or not a light source has been reached.
 *
 *   DESC   : Tests if the ray has made any collisions. If so, the ray is
 *            put on the correct path according to the transmittence of the
 *            object met. The attenuation of this collision is also calculated.
 */
void bounce(inout ray r, inout vec3 attenuation, out bool brk, out bool lit);

/*
 *   PARAMS  : Integers for random sampling. Scene camera. Coordinates of 
 *             current pixel within renderframe. Ray to be made.
 *
 *   DESC    : Creates a ray extending from the camera through the given pixel.
 */
void make_ray(in ivec3 smp, in camera c, in ivec2 px, inout ray r);

/******************************************************************************
 *
 *   prototypes for: `materials.glsl`
 *
 *****************************************************************************/

/*
 *   PARAMS : Record of collision over which to transmit ray. Ray on which to
 *            operate - in: incidence, out: transmitted.
 *
 *   DESC   : Transmits the given ray with respect to the material with which
 *            it has collided.
 */
void transmit(inout hit_record rec, inout ray r);

/*
 *   PARAMS : Record of collision over which to transmit ray. Ray on which to
 *            operate - in: incidence, out: transmitted.
 *
 *   DESC   : Transmission calculation for matte material.
 */
void transmit_matt(in hit_record rec, inout ray r);

/*
 *   PARAMS : Record of collision over which to transmit ray. Ray on which to
 *            operate - in: incidence, out: transmitted.
 *
 *   DESC   : Transmission calculation for reflective material.
 */
void transmit_refl(in hit_record rec, inout ray r);

/*
 *   PARAMS : Record of collision over which to transmit ray. Ray on which to
 *            operate - in: incidence, out: transmitted.
 *
 *   DESC   : Transmission calculation for shiny material.
 */
void transmit_shny(inout hit_record rec, inout ray r);

/*
 *   PARAMS : Record of collision over which to transmit ray. Ray on which to
 *            operate - in: incidence, out: transmitted.
 *
 *   DESC   : Transmission calculation for glass material.
 */
void transmit_glss(in hit_record rec, inout ray r);

/*
 *   PARAMS : Sample vector. Generated random number.
 *
 *   DESC   : Uses a simple hashing function to generate a random float in the
 *            interval [0, 1]. The input sample, `s`, should be fairly
 *            arbitrary but more significantly ever changing. This is because a
 *            given sample s_1 will always give the output r_1.
 */
void random_float(in vec2 s, out float r);

/*
 *   PARAMS : Sample vector. Generated random unit vector.
 *
 *   DESC   : Generates a unit vector that points in some random direction. The
 *            source vector can be any old thing, just hit it with any arbitrary
 *            data.
 */
void random_unit(in vec3 s, out vec3 v);

/*
 *   PARAMS : Cosine of incident angle. Ratio of refraction indices. Specular
 *            reflection coefficient.
 *
 *   DESC   : Schlick's approximation for the specular reflection coefficient
 *            of the given model.
 */
void reflectance(in float cosine, in float ri, out float R);

/******************************************************************************
 *
 *   prototypes for: `objects.glsl`
 *
 *****************************************************************************/

/*
 *   PARAMS : Ray to check collisions for. Minimum distance for the ray to
 *            travel before a collision. Record of collision.
 *
 *   DESC   : Compares given ray with all objects in world. Finds the nearest
 *            of any collisions and records it in the hit record.
 */
void collision(in ray r, in float low, out hit_record rec);

/*
 *   PARAMS : Object that has been hit. Ray to check collisions for. Minimum 
 *            distance for the ray to travel before a collision. Record of 
 *            collision.
 *   
 *   DESC   : Just a switch case, we don't need this now because function
 *            overloading is A-OKAY, although different parameters so maybe we
 *            do...
 *            Uses the shape of the object to determine which algorithm of
 *            collision detection ought to be used.
 */
void hit(in object obj, in ray r, in float low, out hit_record rec);

/*
 *   PARAMS : Object that has been hit. Ray to check collisions for. Minimum 
 *            distance for the ray to travel before a collision. Record of 
 *            collision.
 *
 *   DESC   : Collision detection algorithm for spheres.
 */
void sphere_hit(in object obj, in ray r, in float low, out hit_record rec);

/*
 *   PARAMS : Object that has been hit. Ray to check collisions for. Minimum 
 *            distance for the ray to travel before a collision. Record of 
 *            collision.
 *
 *   DESC   : Collision detection algorithm for planes.
 */
void plane_hit(in object obj, in ray r, in float low, out hit_record rec);