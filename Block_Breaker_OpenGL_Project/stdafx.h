#define CONTINUE 1
#define QUIT 0

int triangleAmount = 20;
struct bricks
{
	float x, y, w, h;
	bool alive;
} b[45], a[50];

float color1[3], color2[3];

struct ball
{
	float ballx, bally, radius, velx, vely;
	float color[3];
	bool left, right, up, down;
} ball;

bool balltemp_l, balltemp_r, balltemp_u, balltemp_d;
float temp_velx, temp_vely;

struct paddle
{
	float myx;
	float myy;
	float width;
	float height;
	bool lft;
	bool rgt;
	float color[3];
}paddle;

bool level2_flag = false;
bool gameover_flag = false;

int hitCount = 0;
float lastCurrentTime, currentTime;
float twicePi = 2.0f * M_PI;

void myinit();
void level2_reshape();
void display_level2();

void specialUp(int, int, int);	//To check for key press
void specialDown(int, int, int);  //To check for key release
void reshape(void);		//To Modify the co-ordinates of the game objects according to the events
void draw(void);		//To Render the Game objects on the screen
void revert(void);
void main_menu(int);
