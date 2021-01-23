#ifdef hgasdd


#include "USART.h"
#define MAX_LEN_MSG  64

u8 check_pack(u_ring* ring,u8* buf, s32 buf_size);

u8 HOT_buffer[MAX_LEN_MSG];
// struct 
//     {
//         u32 rx_size;
//         u8 cold_buffer[USART_DMA_BUF_SIZE];
        
//     }rx_packet;


/*********************
*  Кольцевой буффер  *
**********************/
// #define MAX_LEN_MSG 32

typedef struct 
{
    s8 buffer[MAX_LEN_MSG];
    u32* end_pos_at_end;
    s32 start_pos;
}u_ring;

void init_rb(u_ring* r, u32* ptr_cndt){
    r->start_pos=0;
    r->end_pos_at_end=ptr_cndt;
}

//-----read only----------------
// void push_data(u_ring* ring, u8 c)
// {
//     if(ring->end_pos_at_end==0) 
//     {
//         ring->end_pos_at_end=MAX_LEN_MSG;
//         ring->buffer[MAX_LEN_MSG-ring->end_pos_at_end]=c;
//         return;
//     }
//     ring->buffer[MAX_LEN_MSG-ring->end_pos_at_end]=c;
//     ring->end_pos_at_end--;
//     if(ring->end_pos_at_end<1) {ring->end_pos_at_end=MAX_LEN_MSG;}
// }

//-----read only----------------
// void write_data(u_ring* ring, u8* src, u16 n){
//     for (size_t i = 0; i < n; i++)
//     {
//         push_data(ring, src[i]);
//     }
//     return;
// }

u8 pop_data(u_ring* ring)
{
    s8 rv;
    if(ring->start_pos==(MAX_LEN_MSG-(ring->end_pos_at_end[0]))) 
    return 0;
    if (ring->start_pos<MAX_LEN_MSG){
      rv = ring->buffer[ring->start_pos];
      ring->start_pos++;
      if(ring->start_pos==MAX_LEN_MSG)ring->start_pos=0;
      return rv;
    }
    else{
        rv =ring->buffer[ring->start_pos];
        ring->start_pos=0;
      return rv;
      }

}

u8 read_data(u8* dest, u16 n, u_ring* ring)
{
    u8 rv=0;
    for (size_t i = 0; i < n; i++)
    {
       dest[i]=pop_data(ring);
       rv |= dest[i];
    }
    return rv;
}

/*********************
*  //!Кольцевой буффер  *
**********************/

void work(){


    // fd_set fd_in,fd_out;
    // struct timeval tv;
    u32 err_counter=0;
    u32 tx_counter=0;
    u32 rx_counter=0;
    u32 rx_pack_counter=0;

    u32 reg;

    s32 pos;
    // s32 old_pos=USART_DMA_BUF_SIZE;

    u8* pointer=HOT_buffer;
    u8* end_ptr;
    
    u_ring ring;
    init_rb(&ring, DMA1_BASE+DMA_CNDTR5);

    USART_DMA_recv_init(HOT_buffer, MAX_LEN_MSG);

    while(1){  
       
        reg=REGISTER(USART1+USART_SR);
        // проверяем флаги
        if ( reg &(USART_SR_PE|USART_SR_FE|USART_SR_NE|USART_SR_ORE) )
        {
            //ERRORS
            err_counter++;
        //-------------------------------------
        }if( reg & USART_SR_IDLE )
        {
            //обнаружен конец посылки (тишина на линии)
            if(check_pack(&ring, HOT_buffer, MAX_LEN_MSG))
            {   
                //если пришла ненулевая посылка
                rx_pack_counter++;
            }
        //-------------------------------------
        }if( reg & (USART_SR_TC|USART_SR_TXE) ){
            //фрейм передан
            tx_counter++;
        }
        }if( reg & (USART_SR_RXNE) ){
            //пришёл байт
            rx_counter++;
        }



}


//
// void check_pack(s32* pos,u8* end_ptr,u8* pointer){
    
//             *pos = USART_DMA_get_pos();
//             end_ptr=HOT_buffer+USART_DMA_BUF_SIZE-pos;
//             rx_packet.rx_size=0;
//             if(end_ptr<pointer){
//                 rx_packet.rx_size=end_ptr-HOT_buffer;
//                 u32 var0 = HOT_buffer+USART_DMA_BUF_SIZE-pointer;
//                 u_memcpy(rx_packet.cold_buffer, pointer, var0);
//                 u_memcpy(rx_packet.cold_buffer+var0, HOT_buffer, rx_packet.rx_size);
//                 rx_packet.rx_size+=var0;
//             }else if(end_ptr>pointer){
//                 rx_packet.rx_size=end_ptr-pointer;
//                 u_memcpy(rx_packet.cold_buffer, pointer, end_ptr-pointer);
//             }
//             if(rx_packet.rx_size){
//                 puts("data ok");
//             }
// }

u8 check_pack(u_ring* ring,u8* buf, s32 buf_size)
{
    
            ring->end_pos_at_end = USART_DMA_get_pos();

            return read_data(buf, buf_size, ring);
}
/*
[0 1 2 3 4 5 6 7] 8 p0

[h e l l o      ] 3 p0 p8-3
[L O l l o H E L] 6 p8-3 p8-6

*/

#endif // DEBUG