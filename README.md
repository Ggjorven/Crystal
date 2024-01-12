# Crystal Game Engine
- [Werkplan](#werkplan)
- [Verslag](#verslag)

## <a id="werkplan"></a>Werkplan
### Omschrijving
Tot nu toe is “Crystal” een simpele 2D game engine geschreven in C++. Graphics worden gedaan door mijn eigen abstractielaag rondom OpenGL. De engine is opgesplits in een “Core” met alle Renderer2D/Vertexbuffer/Vertexarray functionaliteit. En een “Physics” gedeelte met een start van een Entity Component System om componenten van “Entity’s” goed in memory op te slaan zodat je niet memory hoeft te kopieeren als je een entity aan een functie doorgeeft bijvoorbeeld. En een “Editor” project waarin de Engine word gebruikt en dingen laat zien aan het scherm bijvoorbeeld een 2D textured quad.

### Plan
- Een editor bouwen, waarin je een game kan creëren. (ImGui?)
- Een script engine maken om scripts te kunnen runnen op je objecten in je game. (LuaCPP?)
- Vulkan support? (Vulkan SDK?)





  

## <a id="verslag"></a>Verslag

### Crystal Game Engine
![](images/editor.png?raw=true)

Door: [Jorben van der Wal](https://github.com/Ggjorven)\
Klas: H4F\
Datum: 06-01-24

### Inhoud
- [Inleiding](#inleiding)
- [Materiaal/methode](#materiaal/methode)
- [Logboek](#logboek)
- [Resultaten](#resultaten)
- [Discussie](#discussie)

### <a id="inleiding"></a>Inleiding
Ik heb gekozen om een game engine te ontwerpen en te bouwen. Ik heb hiervoor gekozen om meerdere redenen. De eerste reden is dat ik al games aan het maken was in C++ zonder game engine. Het probleem hiermee is alleen dat je als je een game maakt steeds dezelfde stappen opnieuw moet maken/coderen. Een game engine doet dat voor je en geeft je 'tools' om het creëren van een game makkelijker te maken. Ik heb het maken van een game engine op dat moment toch uitgesteld, want ik had verwacht dat dit een veelste groot en ingewikkeld project zou worden. Later zag ik een man op YouTube die ook zijn eigen game engine maakte. Dit gaf mij genoeg inspiratie om dit zelf ook te doen. Vandaar nu dit project.

### <a id="materiaal/methode"></a>Materiaal/methode
Ik heb alles gecodeerd op een Windows machine in C++. Ik heb dit gedaan omdat ik al C++ kende en ik weet dat C++ de snelste object georiënteerde taal is. Ik heb gebruikt gemaakt Microsoft Visual Studio vanwege de goeie support van C++. Om grafisch iets te laten zien om een scherm heb ik gebruik gemaakt van de rendering API: "OpenGL". Ik heb deze keuze gemaakt omdat de YouTube vanwaar ik inspiratie kreeg dit ook gebruikte en omdat hij hier een tutorial serie van 30+ afleveringen over heeft gemaakt. Bij de start van dit project wist ik nog helemaal niks over OpenGL. Ik ging OpenGL leren door middel van deze [tutorial serie](https://youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&si=yUkb6EtndogkLLVr) en door [learnopengl](https://learnopengl.com/). Om meer te leren over hoe een game engine in elkaar zit qua architectuur heb ik nog diverse tutorials over game engine architectuur gekeken.
Om het scripten van een game engine op te zetten heb ik veel C# gebruikt. Lua heb ik ook gebruikt om de Microsoft Visual Studio project bestanden met elkaar te linken.

### <a id="logboek"></a>Logboek
#### In hoofdlijnen heb ik mijn engine zo gebouwd:
- Een window creëren
- OpenGL toevoegen aan het project
- Een 2D renderer maken
- Cameras toevoegen
- Een [Entity Component System](https://en.wikipedia.org/wiki/Entity_component_system) maken met mijn eigen storage.
- Eigen project bestanden (.crproj) & (.crscene)
- Een real-time editor bouwen
- C# Scripting toevoegen
- Collision detectie toevoegen
- Een simpele 3D renderer bouwen

Om dieper in alle stappen te gaan kunt u mijn github commits bekijken:
- De link voor het eerste gedeelte van het logboek staat hier: [Commits 1](https://github.com/Ggjorven/Express-Engine/commits/master/)
- Het tweede gedeelte staat hier: [Commits 2](https://github.com/Ggjorven/Crystal/commits/master/)\
Op deze twee sites kunt u onder aan de pagina door gaan naar de volgende commits.

### <a id="resultaten"></a>Resultaten
Het begon allemaal met een simpele driehoek:
![](images/triangle.png?raw=true)

Maar inmiddels ziet het er zo uit:
![](images/editor.png?raw=true)

Het resultaat is dus nu een goedwerkende game engine waarmee je vooral 2D games kunt maken. De engine zorgt ervoor dat je alleen nog maar entities hoeft aan te maken en zelf een script te schrijven in C# en voila je hebt een game die je kan shippen via de Crystal Runtime. De engine bestaat uit meerdere versies de editor en de runtime. Deze 2 samen vormen 9000+ regels aan code in zowel C++ als C#.


### <a id="discussie"></a>Discussie
Ik heb tijdens dit project veel geleerd. Ik snap C++ veel beter dan toen ik begon met dit project. Toen ik starte codeerde ik op een python manier in C++, dit is niet optimaal. Na veel te coderen in C++ snap ik meer hoe de compiler naar de code kijkt en hoe ik de code op laag niveau kan optimaliseren. Voor dit project had ik geen enkele kennis van C# en Lua. Maar om dit project te bouwen heb ik beide tot een bepaald niveau moeten leren. Ook heb ik geleerd hoe de graphische pijplijn werkt en hoe de videokaart kijkt naar data. Dit allemaal met OpenGL.
Alleen niet alles ging natuurlijk soepel. Ik heb veel memory leaks gehad die ik heb moeten fixen, beide op de CPU en GPU. Ik heb [Stackoverflow](https://stackoverflow.com/) en [GPT-4](https://chat.openai.com/) gebruikt om deze problemen op te lossen. Ik heb ook naar oplossing gezocht door iets aan te passen en te proberen en aan te passen en weer te proberen tot dat het werkt. Ik heb geleerd dat je moet oppassen met heap memory en je zo veel mogelijk memory op de stack wilt hebben (zie Probleem 2).

### Voorbeelden
#### Probleem 1:
Als ik binnen in mijn editor tussen mijn scene's binnen in mijn game switch zie ik dat de memory wel omhoog gaat maar niet meer naar beneden. Oftewel een memory leak. Maar waar?
Om dit probleem op te lossen ben ik op elk punt van mijn code gaan kijken hoe hoog de memory usage was en dan te kijken wanneer gaat het omhoog. Leuk en aardig, maar eigenlijk wil ik weten waarom het niet weer naar beneden gaat. Wat ik ook heb geprobeerd is een [deleaker](https://www.deleaker.com/) software te gebruiken. Het probleem was dat ik hier niks van snapte. Ik heb over dit probleem lang na gedacht en ik dacht misschien kan de Visual Studio Performance profiler mij helpen. Ik heb 2 snapshots gemaakt van de memory, 1 voor dat het omhoog gaat en 1 daarna. Daarna heb ik ze vergeleken en zag ik waar de memory vandaan kwam en niet werd opgeruimd. Gefixt.
```cpp
OpenGLTexture2D::~OpenGLTexture2D()
	{
		if (m_Data) stbi_image_free((void*)m_Data); // Deze line was ik vergeten.
		glDeleteTextures(1, &m_RendererID);
	}
 ```

#### Probleem 2:
Ik wilde graag dat als ik mijn runde dat hij na dat ik de game stopte weer terug ging naar de originele staat. Simpel genoeg dacht ik. Ik dacht ik kopieer gewoon mijn eigen Storage class waar alle informatie over alles in de scene in staat en sla die kopie gewoon op.
Zo simpel was het echter niet. In mijn storage class gebruikte ik het 'new' keyword wat memory op de heap aanmaakt. Dit betekent dat mijn Storage de memory eigenlijk niet 'ownt'. Hier kwam het probleem vandaan. Ik probeerde memory te kopieren dat niet van 'mij' was. Dit kan niet en zorgde ervoor dat mijn engine crashte.\
Om dit op te lossen heb ik het 'new' keyword weg gehaald en alle memory op de stack aan te maken direct in mijn Storage class. Dit betekent dat ik alles kan met alle memory wat ik maar wil. Ik wist dat ik dit zo moest oplossen omdat ik zelf al verstand heb van de heap en de stack en dus door te kijken naar hoe de memory in mijn class werkte dacht ik meteen het probleem te zien. En mijn vermoedens waren correct.
```cpp
// Notitie: Dit is niet code die word gebruikt in mijn engine, maar om te laten zien wat ik bedoel.
Foo::Foo()
{
    m_Component = new Component(NULL);
    delete m_Component; // Deze word gecalled in de destructor
    // verandert naar
    m_Component = Component(NULL);
}
```

### Dingen die ik anders zou doen
- Een uitgebreider werkplan maken, met als doel dat het stappenplan helder is van tevoren.
- Al mijn stappen duidelijk noteren in mijn logboek.
- Een minder groot project kiezen.

### Bekijk mijn project op [github](https://github.com/Ggjorven/Crystal/tree/master)
