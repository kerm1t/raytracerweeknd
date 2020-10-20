// raytracerweeknd.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"

vec3 color(const ray& r, hitable* world, int depth)
{
  hit_record rec;
  if (world->hit(r, 0.001, FLT_MAX, rec))
  {
    ray scattered;
    vec3 attenuation;
    if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
      return attenuation * color(scattered, world, depth + 1);
    }
    else
    {
      return vec3(0, 0, 0);
    }
  }
  else // background, makes a blue-> white pattern
  {
    vec3 unit_dir = Normalize(r.dir());
    float t = 0.5 * (unit_dir.y + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

int main()
{
  const int w = 640;
  const int h = 480;
  const int ns = 100;
  // Render

  std::cout << "P3\n" << w << ' ' << h << "\n255\n";
 
  hitable* list[4];
  list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1,0.2,0.5)));
  list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0))); // that is the green sphere ;-)
  list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.2));
  list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
  hitable* world = new hitable_list(list, 4);
  camera cam;

  for (int j = h - 1; j >= 0; j--)
  {
    std::cerr << "\rScanlines remaining:" << j << std::flush;
    for (int i = 0; i < w; i++)
    {
      vec3 col(0, 0, 0);
      for (int s = 0; s < ns; s++)
      {
        float u = float(i+ rand_f()) / float(w);
        float v = float(j+ rand_f()) / float(h);
        ray r = cam.get_ray(u, v);
        //      vec3 p = r.point_at_param(2.0);
        col += color(r, world, 0);
      }
      col /= float(ns);
//      col *= 255.99;
      int ir = static_cast<int>(255.99*sqrt(col.x));
      int ig = static_cast<int>(255.99 * sqrt(col.y));
      int ib = static_cast<int>(255.99 * sqrt(col.z));

      std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
