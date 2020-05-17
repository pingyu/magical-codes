use std::collections::HashMap;

pub struct KvStore {
    map: HashMap<String, String>,
}

impl KvStore {
    pub fn new() -> KvStore {
        KvStore {
            map: HashMap::new(),
        }
    }

    pub fn set(&mut self, key: String, val: String) {
        self.map.insert(key, val);
    }

    pub fn get(&mut self, key: String) -> Option<String> {
        self.map.get(&key).map(|x| x.to_owned())
    }

    pub fn remove(&mut self, key: String) {
        self.map.remove(&key);
    }
}
