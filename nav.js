$(document).ready(function(){
    $(window).scroll(function(){
       if ($(this).scrollTop() > 100) {
         $('.navbar').addClass('solid-navbar');
       } else {
         $('.navbar').removeClass('solid-navbar');
       }
    });
   });





   