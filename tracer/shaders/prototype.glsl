/******************************************************************************
 *
 *   prototypes for: `main.glsl`
 *
 *****************************************************************************/

/*
 *   PARAMS : Ray that is bouncing. Colour attentuation from bounce.
 *
 *   DESC   : Tests if the ray has made any collisions. If so, the ray is
 *            put on the correct path according to the transmittence of the
 *            object met. The attenuation of this collision is also calculated.
 */
void bounce(inout ray r, out vec3 attenuation);

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
void transmit(in hit_record rec, inout vec3 r);

/*
 *   PARAMS : Record of collision over which to transmit ray. Ray on which to
 *            operate - in: incidence, out: transmitted.
 *
 *   DESC   : Transmission calculation for matte material.
 */
void transmit_matt(in hit_record rec, inout vec3 r);

/*
 *   PARAMS : Record of collision over which to transmit ray. Ray on which to
 *            operate - in: incidence, out: transmitted.
 *
 *   DESC   : Transmission calculation for reflective material.
 */
void transmit_refl(in hit_record rec, inout vec3 r);

/*
 *   PARAMS : Record of collision over which to transmit ray. Ray on which to
 *            operate - in: incidence, out: transmitted.
 *
 *   DESC   : Transmission calculation for shiny material.
 */
void transmit_shny(in hit_record rec, inout vec3 r);

/*
 *   PARAMS : Record of collision over which to transmit ray. Ray on which to
 *            operate - in: incidence, out: transmitted.
 *
 *   DESC   : Transmission calculation for glass material.
 */
void transmit_glss(in hit_record rec, inout vec3 r);

/*
 *   PARAMS : Surface normal at collision. Level by which to "fuzz" reflection.
 *            Ray on which to operate - in: incidence, out: transmitted.
 *
 *   DESC   : Reflects given ray, offsetting it to give fuzz.
 */
void mc_reflect(in vec3 normal, in float fuzz_factor, inout vec3 r);

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
 *   PARAMS : Vector with which to align (vaguely). Level by which to offset.
 *            The offset vector.
 *
 *   DESC   : Creates a unit vector which is fairly consistent to the reference
 *            but is offset by some random amount. The extent of this will be
 *            governed by the fuzz factor.
 */
void fuzz_offset(in vec3 reference, in float fuzz_factor, out vec3 offset);

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
 *   PARAMS : Ray to check collisions for. Record of collision.
 *
 *   DESC   : Compares given ray with all objects in world. Finds the nearest
 *            of any collisions and records it in the hit record.
 */
void collision(in ray r, out hit_record rec);

/*
 *   PARAMS : Object that has been hit. Ray that hit the object. Record of hit.
 *   
 *   DESC   : Just a switch case, we don't need this now because function
 *            overloading is A-OKAY, although different parameters so maybe we
 *            do...
 *            Uses the shape of the object to determine which algorithm of
 *            collision detection ought to be used.
 */
void hit(in object obj, in ray r, out hit_record rec);

/*
 *   PARAMS : Object that has been hit. Ray that hit the object. Record of hit.
 *
 *   DESC   : Collision detection algorithm for spheres.
 */
void sphere_hit(in object obj, in ray r, out hit_record rec);

/*
 *   PARAMS : Object that has been hit. Ray that hit the object. Record of hit.
 *
 *   DESC   : Collision detection algorithm for planes.
 */
void plane_hit(in object obj, in ray r, out hit_record rec)