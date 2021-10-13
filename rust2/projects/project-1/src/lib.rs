// #![deny(missing_docs)]

use std::collections::HashMap;

/// KvStore is store of key-value.

pub struct KvStore {
    m: HashMap<String, String>,
}

impl KvStore {
    /// Create a new KvStore object.
    pub fn new() -> Self {
        KvStore { m: HashMap::new() }
    }

    /// Set key to value. Overwrite if existed.
    pub fn set(&mut self, key: String, value: String) {
        self.m.insert(key, value);
    }

    /// Get value of key.
    pub fn get(&self, key: String) -> Option<String> {
        self.m.get(&key).map(|k| k.to_owned())
    }

    /// Remove entry of key.
    /// Keep silence even if key is not existed.
    pub fn remove(&mut self, key: String) {
        self.m.remove(&key);
    }
}

impl Default for KvStore {
    fn default() -> Self {
        Self::new()
    }
}

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }
}
