#![feature(proc_macro_hygiene, decl_macro)]

#[macro_use]
extern crate rocket;

#[macro_use]
extern crate serde_derive;

use rocket_contrib::json::Json;

#[derive(Serialize)]
struct Message {
    id: u64,
    text: String,
}

#[get("/messages")]
fn index() -> Json<Vec<Message>> {
    Json(vec![
        Message {
            id: 1,
            text: "This is a message from the server.".to_string(),
        },
        Message {
            id: 2,
            text: "This is another message from the server.".to_string(),
        },
    ])
}

fn main() {
    rocket::ignite().mount("/api/v1", routes![index]).launch();
}
