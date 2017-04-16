float calculate_fog(in float fog_coord, in vec4 fog_colour, 
					in float fog_start, in float fog_end, 
					in float fog_density) 
{
  // Fog value to return
  float result = 0.0;

  // Calculate (linear) fog
  // result = (fog_end - fog_coord) / (fog_end - fog_start);
  result = exp(-fog_density * fog_coord);

  // Result is 1 minus result clamped to 1.0 to 0.0
  result = clamp(1.0 - result, 0.0, 1.0);

  return result;
}