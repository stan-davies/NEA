vec3 bxdf() {
        // colour = 0

        // density of each sample is amount of light in that sample divided by total light from all samples

        // attenuation (light) of current sample * probability that it actually scatters / SOMETHING??

        // attenuation * scattering_pdf * recurse / pdf_value
        // but scattering_pdf and pdf_value are the same?????
        // only sometimes, they could be different
        // can also do some hemispherical scattering_pdf and then change the pdf_value

        // return colour
}

vec3 bRdf(incidence, surface_normal_at_hit, scattered) {
        // cos_theta = dot( normal, unit(scattered.direction) )
        // if cos_theta < 0
                // return 0
        // return cos_theta / pi
}