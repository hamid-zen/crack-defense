#include "game.h"
#include "timer.h"
#include <SFML/Graphics.hpp>
#include<utility>

using frame = int16_t ;
using times = int16_t ;




struct delay {
    bool switch_vertical ;
    position * cells_switch1 ;
    position * cells_switch2 ;
    delta cell1Dx ;
    delta cell2Dx;
    delta cellDxbase;
    bool newline = false;
    float oldspeed ;
    frame last_frame_alignment;
    frame last_garbage;
    t_number angle;
    float scale;
    char score;
    bool activated;
    times time_left;
    t_number combo;
    std::vector<position *> cells_slide ;
    std::vector<position > cells_align ;
};

enum class typeplayer{
    server,client,ai,player,none
};

//TODO: Pourrait prendre le srand
class arbitre
{
public:
    arbitre(t_number ind,typeplayer plyr1=typeplayer::player,typeplayer plyr2=typeplayer::none , unsigned int port=8080);
    void update(t_action x, bool first_player=true);
    void updatePlayer(t_action x, bool first_player=true);
    void updateFirstPlayer(t_action x);
    void updateSecondPlayer(t_action x);
    float getVerticalSpeed() const{return _vertical_speed;}
    void incVerticalSpeed(float x=0.000001){_vertical_speed+=x;}
    game& player1() const;
    game& player2() const;
    void init(t_number seed = 0);
    delay & getDelays(bool first_player=true);
    t_number getFrame() const {return _nb_frame;}
    void setVerticalSpeed_Med(){_vertical_speed = 1.5;};  
    void setVerticalSpeed_Hard(){_vertical_speed = 2;};
    bool jeu_duo() const ;
    void increment_delays_y_pos(delay * delay_to_update) ;
    bool lost() const ;

    bool jeu_res() const;
    bool server_game() const;
    bool connected() const;
    void connect(const sf::IpAddress &server_ip, unsigned int port);
    void connect_client();
    void send_action(const t_action &action);
    sf::Socket::Status recieve_action(t_action &action);
    void send_number(t_number number);
    sf::Socket::Status recieve_number(t_number &number);
    void send_string(std::string message);
    sf::Socket::Status recieve_string(std::string &message);

private:
    std::unique_ptr<game> _player1;
    std::unique_ptr<game> _player2;
    float _vertical_speed;
    t_number _nb_frame;
    std::unique_ptr<delay> delay_player1 ;
    std::unique_ptr<delay> delay_player2 ;
};

