// raytracerweeknd.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include "vec3f.hxx"
#include "ray.h"

vec3 color(const ray& r) // makes a blue-> white pattern
{
  vec3 unit_dir = Normalize(r.dir());
  float t = 0.5 * (unit_dir.y + 1.0);
  return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
  const int w = 1024;
  const int h = 640;

  // Render

  std::cout << "P3\n" << w << ' ' << h << "\n255\n";
  vec3 bottom_left(-2.0, -1.0, -1.0);
  vec3 horiz(4.0, 0.0, 0.0);
  vec3 vert(0.0, 3.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);
  for (int j = h - 1; j >= 0; j--)
  {
    std::cerr << "\rScanlines remaining:" << j << std::flush;
    for (int i = 0; i < w; i++)
    {
      float u = float(i) / float(w);
      float v = float(j) / float(h);
      ray r(origin, bottom_left + u * horiz + v * vert);
      vec3 col = 255.9 * color(r);
      int ir = static_cast<int>(col.x);
      int ig = static_cast<int>(col.y);
      int ib = static_cast<int>(col.z);

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
