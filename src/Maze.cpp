#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "MazeEdge.h"
#include "Maze.h"
#include "DisjointSet.h"
#include "Vertex.h"
#include <GL/glut.h>

//const int DISTANCE_BETWEEN_TWO_NODES = 1;
const float windowWidth = 600;
const float windowHeight = 800;

const double RAD2DEG = 180.0 / M_PI;
const double DEG2RAD = M_PI / 180.0;

Maze *m_graphics = NULL;

Maze::Maze(int r, int c){
    mouseClicked = 0;
    rows = r;
    columns = c;
    totalVertices = rows*columns;
    totalEdges = 0;
    fillGrid();
    generateMaze();
}

/*void Maze::vertical(int row){
    if (row == 1)
        cout << " ";
    else
        cout << "|";

    for (int i = columns*(row-1)+1; i < row*columns; i++)
    {
        MazeEdge w(i, i+1);
        if (find(maze.begin(), maze.end(), w) != maze.end())
            cout << "  |";
        else
            cout << "   ";
    }
    if (row == rows)
        cout << "   ";
    else
        cout << "  |";
    cout << endl;
} 

void Maze::horizontal(int row){
    cout << "+";
    for (int i = columns*(row-1)+1; i <= row*columns; i++)
    {
        MazeEdge w(i, i+columns);
        if (find(maze.begin(), maze.end(), w) != maze.end())
            cout << "--+";
        else
            cout << "  +";
    }
    cout << endl;
} 

void Maze::topbot(){
    cout << "+";
    for (int i = 0; i < columns; i++)
        cout << "--+";
    cout << endl;
} 

void Maze::printMaze(){
    topbot();
    for (int i = 1; i < rows; i++)
    {
        vertical(i);
        horizontal(i);
    }
    vertical(rows);
    topbot();
} */

void Maze::fillGrid(){
    for (int i = 1; i <= rows; i++)
    {
        for(int j = columns*(i-1)+1; j < i*columns; j++)
        {
            MazeEdge w(j, j+1);
            grid.push_back(w);
        }
    }
    for (int i = 1; i < rows; i++)
    {
        for(int j = columns*(i-1)+1; j <= i*columns; j++)
        {
            MazeEdge w(j, j+columns);
            grid.push_back(w);
        }
    }
}

int myrandom (int i){
    return std::rand()%i;
}

void Maze::generateMaze(){
    DisjointSet ds(rows*columns);
    random_shuffle ( grid.begin(), grid.end(), myrandom );
    vector<MazeEdge>::iterator wi = grid.begin();
    while ( ds.numSets() > 1 )
    {
        MazeEdge w = *wi;
        int rx = ds.Find(w.x);
        int ry = ds.Find(w.y);
        if ( rx != ry )
            ds.Union(rx,ry);
        else
            {
                maze.push_back(w);
                totalEdges++;
            }
        ++wi;
    }
    while ( wi != grid.end() )
    {
        maze.push_back(*wi);
        totalEdges++;
        ++wi;
    }
}
void Maze::solveMaze(){
    CarInitialization();
    addVertex();
    addGraphEdge();
    removeGraphEdge();
    //printMaze();
    //cout << "Solve maze: ";
    //solveMazeDFS();
    //solveMazeAStar();
    MainLoop();
}

void Maze::addVertex(){
    for (int i = 1; i <= totalVertices; i++)
    {
        Vertex v(i);
        vertexList.push_back(v);
    }
}

void Maze::addGraphEdge(){
    for (int i = 0; i < totalVertices; i++)
    {
        adjMat.push_back(vector<int>());
    }
    for (int i = 0; i < totalVertices; i++)
    {
        for (int j = 1; j <= totalVertices; j++)
        {
            adjMat[i].push_back(0); //Set adjacency matrix to 0 (all vertices are not connected)
        }
    }
}

void Maze::removeGraphEdge(){
        for (int j = 1; j <= rows; j++) //Vertical edges
        {
            for (int i = columns*(j-1)+1; i < j*columns; i++)
            {
                MazeEdge w(i, i+1);
                if (find(maze.begin(), maze.end(), w) == maze.end()) //If the maze edge "w" is not in the maze
                {
                    //Add the graph edge of 2 vertices
                    adjMat[i-1][i] = 1;
                    adjMat[i][i-1] = 1;
                }
            }
        }
        for (int j = 1; j < rows; j++)
        {
            for (int i = columns*(j-1)+1; i <= j*columns; i++) //Horizontal edges
            {
                MazeEdge w(i, i+columns);
                if (find(maze.begin(), maze.end(), w) == maze.end()) //If the maze edge "w" is not in the maze
                {
                    //Add the graph edge of 2 vertices
                    adjMat[i-1][i-1+columns] = 1;
                    adjMat[i-1+columns][i-1] = 1;
                }
            }
        }
}

/*void Maze::solveMazeDFS(){
    vertexList[start-1].isVisited = true;
    solutionVertexList.push_back(vertexList[start-1].getName());
    myStack.push(vertexList[start-1]);
    while (!myStack.isEmpty())
    {
        int adjVertIndex = getAdjUnvisitedVertexIndex(myStack.peek().getName()-1);
        if (adjVertIndex != -1)
        {
            vertexList[adjVertIndex].isVisited = true;
            solutionVertexList.push_back(vertexList[adjVertIndex].getName());
            myStack.push(vertexList[adjVertIndex]);
            if (adjVertIndex == finish-1) //If reach the last vertex (the exit)
            {
                cout << "Maze solution: ";
                for (vector<int>::iterator i = solutionVertexList.begin(); i != solutionVertexList.end(); ++i)
                    cout << *i << " ";
                break;
            }
        }
        else
        {
            solutionVertexList.pop_back();
            myStack.pop();
        }
    }
}*/

/*int Maze::getAdjUnvisitedVertexIndex(int v){
    for (int i = 0; i <= totalVertices; i++)
    {
        if(adjMat[v][i] == 1 && vertexList[i].isVisited == false)
            return i;
    }
    return -1;
}*/

void Maze::removeSomeEdges(int p){
    percentageEdgeRemove = (double)p/100;
    edgeRemoved = totalEdges*percentageEdgeRemove;
    random_shuffle ( maze.begin(), maze.end(), myrandom);
    for (int i = 1; i <= edgeRemoved; i++)
    {
        maze.pop_back();
    }

    //Re-update the adjacency Matrix
    removeGraphEdge();

    //printMaze();
    //cout << "Solve maze: ";
    //solveMazeAStar();
}

void Maze::solveMazeAStar(){
    addVertex();
    addGraphEdge();
    removeGraphEdge();

    //Determine xFin and yFin
    if (finish%columns == 0)
    {xFin = windowWidth*(columns-0.5)/columns; yFin = windowHeight*(finish/columns-0.5)/rows;}
    else {xFin = windowWidth*(finish%columns-0.5)/columns; yFin = windowHeight*(finish/columns+0.5)/rows;}   

    //Determine xSta and ySta
    if (start%columns == 0)
    {xSta = windowWidth*(columns-0.5)/columns; ySta = windowHeight*(finish/columns-0.5)/rows;}
    else {xSta = windowWidth*(finish%columns-0.5)/columns; ySta = windowHeight*(finish/columns+0.5)/rows;} 

    double gScore[totalVertices];
    double fScore[totalVertices];
    int cameFrom[totalVertices];

    for (int i = 0; i < totalVertices; i++)
    {
        gScore[i] = -1;
        fScore[i] = -1;
        cameFrom[i] = -1;
    }

    openSet.clear();
    closedSet.clear();

    openSet.insert(start);
    gScore[start-1] = 0;
    fScore[start-1] = heuristicCostEstimate(start);
    while(!openSet.empty())
    {
        int current = *openSet.begin();
        double lowest_fScore = fScore[current-1];
        set<int>::iterator it;
        for (it = openSet.begin(); it != openSet.end(); it++)
        {
            if (fScore[*it-1] < lowest_fScore)
            {
                lowest_fScore = fScore[*it-1];
                current = *it;
            }
        }
        if (current == finish)
        {
            reconstructPath(cameFrom, current);
	    break;
        }
        openSet.erase(current);
        closedSet.insert(current);
        /*for each neighbor of current
            if neighbor in closedSet*/
        for (int i = 0; i < totalVertices; i++)
        { //cout << i+1 << "iteration:" <<endl;
            int neighbor = i + 1;
            if (adjMat[current-1][neighbor-1] == 1)
            {
                //if (closedSet.find(neighbor) != closedSet.end()) //10/24/19: Comment this line
                    //continue; //10/24/19: Comment this line
                double tentative_gScore = gScore[current-1] + EdgeWeight(current, neighbor);
//cout << "current: " << current << ", neighbor: " << neighbor << "distance: " << tentative_gScore<<endl;
                /*if (closedSet.find(neighbor) == closedSet.end())
                    openSet.insert(neighbor);
                else if (gScore[neighbor-1] != -1 && tentative_gScore >= gScore[neighbor-1])
                    continue;
                cameFrom[neighbor-1] = current;
                gScore[neighbor-1] = tentative_gScore;
                fScore[neighbor-1] = gScore[neighbor-1] + heuristicCostEstimate(neighbor);*/ //10/24/19: Comment this section
		if (gScore[neighbor-1] == -1 || (gScore[neighbor-1] != -1 && tentative_gScore < gScore[neighbor-1]))
		{
			cameFrom[neighbor-1] = current;
			gScore[neighbor-1] = tentative_gScore;
			fScore[neighbor-1] = gScore[neighbor-1] + heuristicCostEstimate(neighbor);
			if (openSet.find(neighbor) == openSet.end())
				openSet.insert(neighbor);
		}
            }
        }
    }
    //return false;
}

double Maze::EdgeWeight(int current, int neighbor){
	const int alpha = 5;
	int control = 0, currentValue = 0, neighborValue = 0;
	vector<propagation>::iterator ite;
	for (ite = propagationVector.begin(); ite != propagationVector.end(); ite++)
	{
		propagation cur = *ite;
		if (cur.id == current)
		{
			currentValue = cur.value;
			control++;
		}
		else if (cur.id == neighbor)
		{
			neighborValue = cur.value;
			control++;
		}
		if (control == 2)
			break; 
	}
	if (currentValue < neighborValue)
		return 1.0/pow(currentValue, alpha); 
	else return 1.0/pow(neighborValue, alpha);
}

double Maze::heuristicCostEstimate(int startNode){
    int x, y;
    div_t divResult;
    divResult = div(startNode, columns);
    if (divResult.rem == 0)
        x = columns;
    else x = divResult.rem;

    y = startNode/columns + 1;

    return sqrt(pow(abs(x - xFin), 2) + pow(abs(y - yFin), 2));
}

void Maze::reconstructPath(int cameFrom[], int current){
    totalPath.clear();
    int count = 0;
    totalPath.push_back(-1);
    totalPath[count++] = current;
    while (current != start)
    {
	totalPath.push_back(-1);
        current = cameFrom[current-1];
        totalPath[count++] = current;
    }
}

void Maze::MainLoop(void){
	m_graphics = this;
	static int argc = 1;
	static char *args = (char*)"args";
	glutInit(&argc, &args);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Maze");

	glutDisplayFunc(CallbackEventOnDisplay);
	glutMouseFunc(CallbackEventOnMouse);
	glutKeyboardFunc(CallbackEventOnNormalKeyPress);

	//Enter main event loop
	glutMainLoop();
}

void Maze::CallbackEventOnNormalKeyPress(unsigned char key, int x, int y){
	if (m_graphics && m_graphics->HandleEventOnNormalKeyPress(key))
		glutPostRedisplay();
}

void Maze::CallbackEventOnDisplay(){
	if (m_graphics)
	{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, windowWidth, windowHeight, 0.0f, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	m_graphics->HandleEventOnDisplay();
	glutPostRedisplay();
	glutSwapBuffers();
	}
}

bool Maze::HandleEventOnNormalKeyPress(const int key){
	if (key == 27) //exit key
	{
		exit(0);
		return true;
	}
	else if (key == 'a')
		carState[STATE_X] -= STATE_MOVE_X;
	else if (key == 'd')
		carState[STATE_X] += STATE_MOVE_X;
	else if (key == 'w')
		carState[STATE_Y] -= STATE_MOVE_Y;
	else if (key == 's')
		carState[STATE_Y] += STATE_MOVE_Y;
	else if (key == 'e')
		carState[STATE_THETA] += STATE_MOVE_THETA;
	else if (key == 'q')
		carState[STATE_THETA] -= STATE_MOVE_THETA;
	else if (key == 'f')
	{
		carState[STATE_X] += STATE_MOVE_X * cos(carState[STATE_THETA]);
		carState[STATE_Y] += STATE_MOVE_Y * sin(carState[STATE_THETA]);
	}
	else if (key == 'b')
	{
		carState[STATE_X] -= STATE_MOVE_X * cos(carState[STATE_THETA]);
		carState[STATE_Y] -= STATE_MOVE_Y * sin(carState[STATE_THETA]);
	}
	return true;
}

void Maze::HandleEventOnDisplay(){

	if (mouseClicked >= 2 )
	{ColorClearance();}
	if (mouseClicked >= 3)
	{DrawStart();}
	glDisable(GL_DEPTH_TEST);
	if (mouseClicked >= 4)
	{
		DrawFinish();
		DrawSolution();
	}

	glColor3f(0.0f, 1.0f, 0.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	DrawMaze();
	glEnable(GL_DEPTH_TEST);
	
	glPushMatrix();
	glTranslated(carState[STATE_X], carState[STATE_Y], 0.0);
	glTranslatef(-windowWidth / (2.0*columns), -windowHeight / (2.0*columns), 0.0);
	glRotatef(RAD2DEG * carState[STATE_THETA], 0, 0, 1);
	glTranslatef(windowWidth / (2.0*columns), windowHeight / (2.0*columns), 0.0);
	
	glColor3f(1.0f, 0.0f, 0.0f);
	glNormal3d(0, 0, 1);
	glBegin(GL_POLYGON);
	glVertex2d(carDimX / 3.0, carDimY / 3.0);
	glVertex2d(carDimX / 3.0, (2*carDimY) / 3.0);
	glVertex2d((2*carDimX) / 3.0, (2*carDimY) / 3.0);
	glVertex2d((2*carDimX) / 3.0, carDimY / 3.0);
	glEnd();

	glDisable(GL_DEPTH_TEST);
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glVertex2d((2*carDimX) / 3.0, carDimY / 2.0);
	glVertex2d(carDimX / 2.0, carDimY / 2.0);
	glEnd();
	glEnable(GL_DEPTH_TEST);

	glPopMatrix();
}

void Maze::DrawMaze(){
	GLfloat thickness = 5;
	glLineWidth(thickness);
	for (int i = 1; i < rows; i++)
    	{
        DrawVertical(i);
        DrawHorizontal(i);
    	}
    	DrawVertical(rows);
	glLineWidth(1.f);
}

void Maze::DrawVertical(int row){
	glBegin(GL_LINES);
	for (int i = columns*(row-1)+1; i < row*columns; i++)
	{
		MazeEdge w(i, i+1);
        	if (find(maze.begin(), maze.end(), w) != maze.end())
		{
			glVertex2f(windowWidth*((float)(i%columns)/columns), windowHeight*((float)(row-1)/rows));
			glVertex2f(windowWidth*((float)(i%columns)/columns), windowHeight*((float)row/rows));
		}
	}
	glEnd();
}

void Maze::DrawHorizontal(int row){
	//cout << "row: " << row <<endl;
	glBegin(GL_LINES);
   	for (int i = columns*(row-1)+1; i <= row*columns; i++)
  	{//cout << "i: " << i << endl;
		MazeEdge w(i, i+columns);
	        if (find(maze.begin(), maze.end(), w) != maze.end())
		{//cout << "found!" << endl; 
			glVertex2f(windowWidth*((float)(i%columns - 1)/columns),windowHeight*((float)row/rows));
			glVertex2f(windowWidth*((float)(i%columns)/columns),windowHeight*((float)row/rows));
		}
	}
	glEnd();
}

void Maze::DrawStart(){
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(startX, startY);
	glVertex2f((windowWidth*floor((startX*columns)/windowWidth)/columns + windowWidth*ceil((startX*columns)/windowWidth)/columns)/2, (windowHeight*floor((startY*rows)/windowHeight)/rows + windowHeight*ceil((startY*rows)/windowHeight)/rows)/2);
	glEnd();
}

void Maze::DrawFinish(){
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(finishX, finishY);
	glVertex2f((windowWidth*floor((finishX*columns)/windowWidth)/columns + windowWidth*ceil((finishX*columns)/windowWidth)/columns)/2, (windowHeight*floor((finishY*rows)/windowHeight)/rows + windowHeight*ceil((finishY*rows)/windowHeight)/rows)/2);
	glEnd();
}

void Maze::DrawSolution(){
	//Draw from finish to start
	float xNow = 0, yNow = 0, xPast = 0, yPast = 0;
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	for (vector<int>::iterator i = totalPath.begin(); i != totalPath.end(); ++i)
	{
		if (*i == finish)
		{xNow = xFin; yNow = yFin;}
		else if (/*(*i) != start && */(*i) != finish)
		{
			xPast = xNow;
			yPast = yNow;
			if ((*i)%columns == 0)
			{
				xNow = windowWidth*(columns-0.5)/columns;
				yNow = windowHeight*((*i)/columns-0.5)/rows;
				glVertex2f(xPast, yPast);
				glVertex2f(xNow, yNow);
			}
			else
			{
				xNow = windowWidth*((*i)%columns-0.5)/columns;
				yNow = windowHeight*((*i)/columns+0.5)/rows;
				glVertex2f(xPast, yPast);
				glVertex2f(xNow, yNow);
			}
		}
		/*else if (*i == start)
		{
			glVertex2f(xNow, yNow);
			glVertex2f(xSta, ySta);
		}*/
	}
	glEnd();
}

void Maze::ColorClearance(){
	vector<propagation>::iterator ite;
	vector<propagation>::reverse_iterator rite;
	rite = propagationVector.rbegin();
	int maxValue = (*rite).value;
	for (ite = propagationVector.begin(); ite != propagationVector.end(); ite++)
	{
		propagation current = *ite;
		int nrCol, nrRow;
		if (current.id % columns == 0)
		{
			nrCol = columns;
			nrRow = current.id/columns;
		}
		else 
		{
			nrCol = current.id%columns;
			nrRow = current.id/columns + 1;
		}
		
		float color = (float)current.value/maxValue;
		glColor3f(color, color, color);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
		glVertex2f((windowWidth*(nrCol-1))/columns, (windowHeight*(nrRow-1))/rows);
		glVertex2f((windowWidth*(nrCol-1))/columns, (windowHeight*nrRow)/rows);
		glVertex2f((windowWidth*nrCol)/columns, (windowHeight*nrRow)/rows);
		glVertex2f((windowWidth*nrCol)/columns, (windowHeight*(nrRow-1))/rows);
		glEnd();
	}
}

void Maze::CallbackEventOnMouse(int button, int state, int x, int y){
	if (m_graphics && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		double mouseX, mouseY;
		MousePosition(x, y, &mouseX, &mouseY);
		m_graphics -> HandleEventOnMouseLeftButtonDown(mouseX, mouseY);
		glutPostRedisplay();
	}
}

void Maze::HandleEventOnMouseLeftButtonDown(const double mousePosX, const double mousePosY){
	if (mouseClicked == 0)
	{
		removeSomeEdges(95);
		mouseClicked = 1;
	}	

	else if (mouseClicked == 1)
	{
		Propagate(); 
		mouseClicked = 2;
	}
	else if (mouseClicked == 2)
	{
		start = floor(mousePosY*rows/windowHeight)*columns + ceil(mousePosX*columns/windowWidth);
		startX = mousePosX;
		startY = mousePosY;		
		mouseClicked = 3;
	}
	else if (mouseClicked == 3)
	{
		finish = floor(mousePosY*rows/windowHeight)*columns + ceil(mousePosX*columns/windowWidth);
		finishX = mousePosX;
		finishY = mousePosY;
		solveMazeAStar();
		mouseClicked = 4;
	}
}

void Maze::MousePosition(const int x, const int y, double *posX, double *posY){
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLfloat winX, winY, winZ;
	GLdouble posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
	glGetDoublev( GL_PROJECTION_MATRIX, projection );
	glGetIntegerv( GL_VIEWPORT, viewport );

	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, posX, posY, &posZ);
}

void Maze::Propagate(){
	vector<propagation> myPropagation;
	int valueReferenceArray [totalVertices];
	for (int i = 1; i <= totalVertices; i++)
	{
		propagation p;
		p.id = i;
		p.value = 0;
		myPropagation.push_back(p);	
	}
	vector<propagation>::iterator ite;
	for (ite = myPropagation.begin(); ite != myPropagation.end(); ite++)
	{
		propagation current = *ite;
		if (current.id / columns == 0 || current.id / columns == rows - 1 || current.id % columns == 0 || current.id % columns == 1 || isNearWall(current.id))
		{
			current.value = 2;
			propagationVector.push_back(current);
			valueReferenceArray[current.id - 1] = current.value;
			myPropagation.erase(ite--);
		}
	}

	int currentValue = 1;
	while (!myPropagation.empty())
	{
		currentValue++;
		for (ite = myPropagation.begin(); ite != myPropagation.end(); ite++)
		{
			propagation current = *ite;
			if (valueReferenceArray[current.id - 1 - 1] == currentValue ||
				valueReferenceArray[current.id - 1 + 1] == currentValue ||
				valueReferenceArray[current.id - 1 - columns] == currentValue ||
				valueReferenceArray[current.id - 1 + columns] == currentValue)
			{
				current.value = currentValue + 1;
				propagationVector.push_back(current);
				valueReferenceArray[current.id - 1] = current.value;
				myPropagation.erase(ite--);
			}
		}
	}
}

bool Maze::isNearWall(int id){
	if (adjMat[id-1][id-1-1] == 0 || adjMat[id-1][id+1-1] == 0 || adjMat[id-1][id-1-columns] == 0 || adjMat[id-1][id-1+columns] == 0)
		return true;
	else return false;
}

void Maze::CarInitialization(){
	STATE_MOVE_X = windowWidth / (6.0 * columns);
	STATE_MOVE_Y = windowHeight / (6.0 * rows);
	STATE_MOVE_THETA = 2.0 * DEG2RAD;
	carState[STATE_X] = carState[STATE_Y] = carState[STATE_THETA] = 0.0;
	carDimX = windowWidth / columns;
	carDimY = windowHeight / rows;
}
