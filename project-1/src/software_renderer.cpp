#include "software_renderer.h"

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>

#include "triangulation.h"

using namespace std;

namespace CS248 {

unsigned char* supersample_target;

// formula para pixel (4 * (x + y * target_w))
// 

// fill a sample location with color
void SoftwareRendererImp::fill_sample(int sx, int sy, const Color &color) {
  // check bounds
  // sx = sample number
  // sy = pixel number

  // [1.1.r, 1.1.g, 1.1.b, 1.1.a, 1.2.r, 1.2.g, 1.2.b, 1.2.a, 1.3.r, 1.3.g, 1.3.b, 1.3.a, 1.4.r, 1.4.g, 1.4.b, 1.4.a, 2.1.r, ..]

  int sampleRateSquared = sample_rate * sample_rate;
	if (sx < 0 || sx >= sampleRateSquared) return;
	if (sy < 0 || sy >= target_w*target_h) return;

	supersample_target[4 * sampleRateSquared * sy + sx*4] = (uint8_t)(color.r * 255);
	supersample_target[4 * sampleRateSquared * sy + sx*4 + 1] = (uint8_t)(color.g * 255);
	supersample_target[4 * sampleRateSquared * sy + sx*4 + 2] = (uint8_t)(color.b * 255);
	supersample_target[4 * sampleRateSquared * sy + sx*4 + 3] = (uint8_t)(color.a * 255);
}

// fill samples in the entire pixel specified by pixel coordinates
void SoftwareRendererImp::fill_pixel(int x, int y, const Color &color) {

	// Task 2: Re-implement this function
  int sampleRateSquared = sample_rate * sample_rate;
  
  if (x < 0 || x >= target_w) return;
	if (y < 0 || y >= target_h) return;

	Color pixel_color;
	float inv255 = 1.0 / 255.0;
  int r = 0;
  int g = 0;
  int b = 0;
  int a = 0;
  for (int sx = 0; sx < sampleRateSquared; sx++) {
    r += supersample_target[ 4 * sampleRateSquared * (x + y * target_w) + sx * 4];
    g += supersample_target[ 4 * sampleRateSquared * (x + y * target_w) + (sx * 4) + 1];
    b += supersample_target[ 4 * sampleRateSquared * (x + y * target_w) + (sx * 4) + 2];
    a += supersample_target[ 4 * sampleRateSquared * (x + y * target_w) + (sx * 4) + 3];
  }
  pixel_color.r = r/sampleRateSquared;
  pixel_color.g = g/sampleRateSquared;
  pixel_color.b = b/sampleRateSquared;
  pixel_color.a = a/sampleRateSquared;

	pixel_color = ref->alpha_blending_helper(pixel_color, color);

  for (int sx = 0; sx < sampleRateSquared; sx++) {
    supersample_target[ 4 * sampleRateSquared * (x + y * target_w) + sx * 4] = (uint8_t)(pixel_color.r * 255);
    supersample_target[ 4 * sampleRateSquared * (x + y * target_w) + (sx * 4) + 1] = (uint8_t)(pixel_color.g * 255);
    supersample_target[ 4 * sampleRateSquared * (x + y * target_w) + (sx * 4) + 2] = (uint8_t)(pixel_color.b * 255);
    supersample_target[ 4 * sampleRateSquared * (x + y * target_w) + (sx * 4) + 3] = (uint8_t)(pixel_color.a * 255);
  }


/*
	// check bounds
	if (x < 0 || x >= target_w) return;
	if (y < 0 || y >= target_h) return;

	Color pixel_color;
	float inv255 = 1.0 / 255.0;
	pixel_color.r = render_target[4 * (x + y * target_w)] * inv255;
	pixel_color.g = render_target[4 * (x + y * target_w) + 1] * inv255;
	pixel_color.b = render_target[4 * (x + y * target_w) + 2] * inv255;
	pixel_color.a = render_target[4 * (x + y * target_w) + 3] * inv255;

	pixel_color = ref->alpha_blending_helper(pixel_color, color);

	render_target[4 * (x + y * target_w)] = (uint8_t)(pixel_color.r * 255);
	render_target[4 * (x + y * target_w) + 1] = (uint8_t)(pixel_color.g * 255);
	render_target[4 * (x + y * target_w) + 2] = (uint8_t)(pixel_color.b * 255);
	render_target[4 * (x + y * target_w) + 3] = (uint8_t)(pixel_color.a * 255);
*/
}

void SoftwareRendererImp::draw_svg( SVG& svg ) {

  // set top level transformation
  transformation = canvas_to_screen;

  // draw all elements
  for ( size_t i = 0; i < svg.elements.size(); ++i ) {
    draw_element(svg.elements[i]);
  }

  // draw canvas outline
  Vector2D a = transform(Vector2D(    0    ,     0    )); a.x--; a.y--;
  Vector2D b = transform(Vector2D(svg.width,     0    )); b.x++; b.y--;
  Vector2D c = transform(Vector2D(    0    ,svg.height)); c.x--; c.y++;
  Vector2D d = transform(Vector2D(svg.width,svg.height)); d.x++; d.y++;

  rasterize_line(a.x, a.y, b.x, b.y, Color::Black);
  rasterize_line(a.x, a.y, c.x, c.y, Color::Black);
  rasterize_line(d.x, d.y, b.x, b.y, Color::Black);
  rasterize_line(d.x, d.y, c.x, c.y, Color::Black);

  // resolve and send to render target
  resolve();

}

void SoftwareRendererImp::set_sample_rate( size_t sample_rate ) {

  // Task 2: 
  // You may want to modify this for supersampling support
  this->sample_rate = sample_rate;

  //Crear Arreglo Supersampling_target
  supersample_target = (unsigned char*) malloc(4 * target_h * target_w * sample_rate * sample_rate * sizeof(uint8_t));
  memset(supersample_target, 255, 4 * target_w * target_h * sample_rate * sample_rate);

}

void SoftwareRendererImp::set_render_target( unsigned char* render_target,
                                             size_t width, size_t height ) {

  // Task 2: 
  // You may want to modify this for supersampling support
  this->render_target = render_target;
  this->target_w = width;
  this->target_h = height;
  supersample_target = (unsigned char*) malloc(4 * target_h * target_w * sample_rate * sample_rate * sizeof(uint8_t));
  memset(supersample_target, 255, 4 * target_w * target_h * sample_rate * sample_rate);

}

void SoftwareRendererImp::draw_element( SVGElement* element ) {

	// Task 3 (part 1):
	// Modify this to implement the transformation stack

	switch (element->type) {
	case POINT:
		draw_point(static_cast<Point&>(*element));
		break;
	case LINE:
		draw_line(static_cast<Line&>(*element));
		break;
	case POLYLINE:
		draw_polyline(static_cast<Polyline&>(*element));
		break;
	case RECT:
		draw_rect(static_cast<Rect&>(*element));
		break;
	case POLYGON:
		draw_polygon(static_cast<Polygon&>(*element));
		break;
	case ELLIPSE:
		draw_ellipse(static_cast<Ellipse&>(*element));
		break;
	case IMAGE:
		draw_image(static_cast<Image&>(*element));
		break;
	case GROUP:
		draw_group(static_cast<Group&>(*element));
		break;
	default:
		break;
	}

}


// Primitive Drawing //

void SoftwareRendererImp::draw_point( Point& point ) {

  Vector2D p = transform(point.position);
  rasterize_point( p.x, p.y, point.style.fillColor );

}

void SoftwareRendererImp::draw_line( Line& line ) { 

  Vector2D p0 = transform(line.from);
  Vector2D p1 = transform(line.to);
  rasterize_line( p0.x, p0.y, p1.x, p1.y, line.style.strokeColor );

}

void SoftwareRendererImp::draw_polyline( Polyline& polyline ) {

  Color c = polyline.style.strokeColor;

  if( c.a != 0 ) {
    int nPoints = polyline.points.size();
    for( int i = 0; i < nPoints - 1; i++ ) {
      Vector2D p0 = transform(polyline.points[(i+0) % nPoints]);
      Vector2D p1 = transform(polyline.points[(i+1) % nPoints]);
      rasterize_line( p0.x, p0.y, p1.x, p1.y, c );
    }
  }
}

void SoftwareRendererImp::draw_rect( Rect& rect ) {

  Color c;
  
  // draw as two triangles
  float x = rect.position.x;
  float y = rect.position.y;
  float w = rect.dimension.x;
  float h = rect.dimension.y;

  Vector2D p0 = transform(Vector2D(   x   ,   y   ));
  Vector2D p1 = transform(Vector2D( x + w ,   y   ));
  Vector2D p2 = transform(Vector2D(   x   , y + h ));
  Vector2D p3 = transform(Vector2D( x + w , y + h ));
  
  // draw fill
  c = rect.style.fillColor;
  if (c.a != 0 ) {
    rasterize_triangle( p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, c );
    rasterize_triangle( p2.x, p2.y, p1.x, p1.y, p3.x, p3.y, c );
  }

  // draw outline
  c = rect.style.strokeColor;
  if( c.a != 0 ) {
    rasterize_line( p0.x, p0.y, p1.x, p1.y, c );
    rasterize_line( p1.x, p1.y, p3.x, p3.y, c );
    rasterize_line( p3.x, p3.y, p2.x, p2.y, c );
    rasterize_line( p2.x, p2.y, p0.x, p0.y, c );
  }

}

void SoftwareRendererImp::draw_polygon( Polygon& polygon ) {

  Color c;

  // draw fill
  c = polygon.style.fillColor;
  if( c.a != 0 ) {

    // triangulate
    vector<Vector2D> triangles;
    triangulate( polygon, triangles );

    // draw as triangles
    for (size_t i = 0; i < triangles.size(); i += 3) {
      Vector2D p0 = transform(triangles[i + 0]);
      Vector2D p1 = transform(triangles[i + 1]);
      Vector2D p2 = transform(triangles[i + 2]);
      rasterize_triangle( p0.x, p0.y, p1.x, p1.y, p2.x, p2.y, c );
    }
  }

  // draw outline
  c = polygon.style.strokeColor;
  if( c.a != 0 ) {
    int nPoints = polygon.points.size();
    for( int i = 0; i < nPoints; i++ ) {
      Vector2D p0 = transform(polygon.points[(i+0) % nPoints]);
      Vector2D p1 = transform(polygon.points[(i+1) % nPoints]);
      rasterize_line( p0.x, p0.y, p1.x, p1.y, c );
    }
  }
}

void SoftwareRendererImp::draw_ellipse( Ellipse& ellipse ) {

  // Extra credit 

}

void SoftwareRendererImp::draw_image( Image& image ) {

  Vector2D p0 = transform(image.position);
  Vector2D p1 = transform(image.position + image.dimension);

  rasterize_image( p0.x, p0.y, p1.x, p1.y, image.tex );
}

void SoftwareRendererImp::draw_group( Group& group ) {

  for ( size_t i = 0; i < group.elements.size(); ++i ) {
    draw_element(group.elements[i]);
  }

}

// Rasterization //

// The input arguments in the rasterization functions 
// below are all defined in screen space coordinates

void SoftwareRendererImp::rasterize_point( float x, float y, Color color ) {

  // fill in the nearest pixel
  int sx = (int)floor(x);
  int sy = (int)floor(y);

  // check bounds
  if (sx < 0 || sx >= target_w) return;
  if (sy < 0 || sy >= target_h) return;

  // fill sample - NOT doing alpha blending!
  // TODO: Call fill_pixel here to run alpha blending
  fill_pixel(sx, sy, color);
  /*
  render_target[4 * (sx + sy * target_w)] = (uint8_t)(color.r * 255);
  render_target[4 * (sx + sy * target_w) + 1] = (uint8_t)(color.g * 255);
  render_target[4 * (sx + sy * target_w) + 2] = (uint8_t)(color.b * 255);
  render_target[4 * (sx + sy * target_w) + 3] = (uint8_t)(color.a * 255);
  */
}

void SoftwareRendererImp::rasterize_line( float x0, float y0,
                                          float x1, float y1,
                                          Color color) {

  // Extra credit (delete the line below and implement your own)
  //ref->rasterize_line_helper(x0, y0, x1, y1, target_w, target_h, color, this);
  int xx0 = (int)floor(x0);
  int xx1 = (int)floor(x1);
  int yy0 = (int)floor(y0);
  int yy1 = (int)floor(y1);

  int dx = abs(xx1 - xx0);
  int sx = xx0<xx1 ? 1 : -1;
  int dy = -abs(yy1 - yy0);
  int sy = yy0<yy1 ? 1 : -1;
  int err = dx+dy;
  while(true) {
    fill_pixel(xx0, yy0, color);
    if (xx0 == xx1 && yy0 == yy1) break;
    int e2 = 2*err;
    if (e2 >= dy){
      err += dy;
      xx0 += sx;
    }
    
    if (e2 <= dx) {
      err += dx;
      yy0 += sy;
    }
  }
}

bool insideEdge(float x, float y, float x0, float y0, float x1, float y1) {
  float dy = y1 - y0;
  float dx = x1 - x0;
  float c = y0 * (x1 - x0) - x0 * (y1 - y0);

  float l = dy*x - dx*y + c;
  return l <= 0;
}

void SoftwareRendererImp::rasterize_triangle( float x0, float y0,
                                              float x1, float y1,
                                              float x2, float y2,
                                              Color color ) {
  // Task 1: 
  // Implement triangle rasterization (you may want to call fill_sample here)

  float maxX = fmax(x0, fmax(x1, x2));
  float minX = fmin(x0, fmin(x1, x2));

  float maxY = fmax(y0, fmax(y1, y2));
  float minY = fmin(y0, fmin(y1, y2));

  double invSampleRate = 1.0 / sample_rate;
  double halveInvSampleRate = invSampleRate / 2;
  int sampleRateSquared = sample_rate * sample_rate;

  float stepX, stepY;

  for(int x = minX; x < maxX; x++) {
    for (int y = minY; y < maxY; y++) {

      for (int sx = 0; sx < sample_rate; sx++) {
        stepX = halveInvSampleRate + invSampleRate*sx;

        for (int sy = 0; sy < sample_rate; sy++) {
          // 1/(2*SR) + (1/SR)*Sx
          stepY = halveInvSampleRate + invSampleRate*sy;
          if( insideEdge(x + stepX, y + stepY, x0, y0, x1, y1) &&
              insideEdge(x + stepX ,y + stepY, x1, y1, x2, y2) &&
              insideEdge(x + stepX, y + stepY, x2, y2, x0, y0)) {
            
            int sampleX = sx + sy * sample_rate;  // sample number
            int sampleY = x + y * target_w;       // pixel number

            fill_sample(sampleX, sampleY, color);

            // [1.1.r, 1.1.g, 1.1.b, 1.1.a, 1.2.r, 1.2.g, 1.2.b, 1.2.a, 1.3.r, 1.3.g, 1.3.b, 1.3.a, 1.4.r, 1.4.g, 1.4.b, 1.4.a, 2.1.r, ..]
          
          }
        }
      }
    }
  }
}

void SoftwareRendererImp::rasterize_image( float x0, float y0,
                                           float x1, float y1,
                                           Texture& tex ) {
  // Task 4: 
  // Implement image rasterization (you may want to call fill_sample here)

}

// resolve samples to render target
void SoftwareRendererImp::resolve( void ) {

  // Task 2: 
  // Implement supersampling
  // You may also need to modify other functions marked with "Task 2".

  int sampleRateSquared = sample_rate * sample_rate;

  for(int x = 0; x < target_w; x++) {
    for (int y = 0; y < target_h; y++) {
      int r = 0;
      int g = 0;
      int b = 0;
      int a = 0;

      for (int sx = 0; sx < sampleRateSquared; sx++) {
        r += supersample_target[ 4 * sampleRateSquared * (x + y * target_w) + sx * 4];
        g += supersample_target[ 4 * sampleRateSquared * (x + y * target_w) + (sx * 4) + 1];
        b += supersample_target[ 4 * sampleRateSquared * (x + y * target_w) + (sx * 4) + 2];
        a += supersample_target[ 4 * sampleRateSquared * (x + y * target_w) + (sx * 4) + 3];
      }

      render_target[4 * (x + y * target_w)] = r/sampleRateSquared;
      render_target[4 * (x + y * target_w) + 1] = g/sampleRateSquared;
      render_target[4 * (x + y * target_w) + 2] = b/sampleRateSquared;
      render_target[4 * (x + y * target_w) + 3] = a/sampleRateSquared;

      // [1.1.r, 1.1.g, 1.1.b, 1.1.a, 1.2.r, 1.2.g, 1.2.b, 1.2.a, 1.3.r, 1.3.g, 1.3.b, 1.3.a, 1.4.r, 1.4.g, 1.4.b, 1.4.a, 2.1.r, ..]
      
    }
  }
  
  //free(supersample_target);
  return;

}

Color SoftwareRendererImp::alpha_blending(Color pixel_color, Color color)
{
  // Task 5
  // Implement alpha compositing
  return pixel_color;
}


} // namespace CS248
