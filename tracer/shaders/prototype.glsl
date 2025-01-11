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
 *   PARAMS : Ray that is bouncing. Colour attentuation from bounce.
 *
 *   DESC   : Tests if the ray has made any collisions. If so, the ray is
 *            put on the correct path according to the transmittence of the
 *            object met. The attenuation of this collision is also calculated.
 */
void bounce(inout ray r, out vec3 attenuation);