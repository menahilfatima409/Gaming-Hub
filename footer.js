function sendMail(){
    var params = {
        name: document.getElementById("name").value,
        email: document.getElementById("email").value,
       

    };
   const serviceID = "service_iepnnv5";
   const templateID = "template_5bj0q0f";

   emailjs
   .send(serviceID, templateID, params)
    .then((res) => {
        document.getElementById("name").value = "";
        document.getElementById("email").value = "";
        console.log(res);
        alert("successfull");
    })
    .catch((err) => console.log(err));

}
