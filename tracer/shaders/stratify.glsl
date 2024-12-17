float get_strat_coef() {
        // curr_px_tl = pixel00 + (coords.x * pixel_du)    top left of current pixel
        // curr_px_br = curr_px_tl + pixel_du + pixel_dv    bottom right of current pixel

        // a = curr_px_tl - (stratified_offset * -(pixel_du + pixel_dv))
        // b = curr_px_br + (stratified_offset *  (pixel_du + pixel_dv))

        // pixel_coef = 1 / (b - a)

        // return pixel_coef




        // n (number of samples), 

        // dx = (b - a) / n
}